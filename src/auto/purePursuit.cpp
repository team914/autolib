#include "autolib/auto/purePursuit.hpp"

namespace autolib{

/**
 * PurePursuit::PurePursuit 
 * 
 * @param  {InternalPath} iipath               : 
 * @param  {okapi::QLength} ilookaheadDistance : 
 */
PurePursuit::PurePursuit( const std::vector<PosePath> &ipaths, const okapi::QLength &ilookaheadDistance ){
    #ifdef DEBUG
        printf( "\tInheriting Points from Path\n" );
    #endif
    lookaheadDistance = ilookaheadDistance.convert(meter);
}

/**
 * PurePursuit 
 * 
 * @param  {okapi::QLength} ix    : 
 * @param  {okapi::QLength} iy    : 
 * @param  {okapi::QAngle} itheta : 
 * @return {Curvature}            : 
 */
Curvature PurePursuit::getGoalCurvature( const Pose &ipose, const std::string &iid ){
    path = findPath( iid );
    findNearestPose( ipose );
    findGoalPose();
    convertGlobalToLocalPose();
    return findCurvature();
}

void PurePursuit::findNearestPose( const InternalPose &ipose ){
    currentPose.path.emplace_back( ipose );
    if( nearestPoses.path.empty() ){
        int poseIndex = 0;
        double distance = findDistanceBetweenPoses( path.path.at(0), ipose );
        InternalDistancePoseIndexed nearestPose{ipose, poseIndex, distance};
        for( auto &&pose: path.path ){
            distance = findDistanceBetweenPoses( pose, ipose );
            if( distance < nearestPose.distance )
                nearestPose = InternalDistancePoseIndexed( pose, i, distance );
            poseIndex++;
        }
    }else{
        int i = nearestPoses.path.end().index;
        double distance = nearestPoses.path.end().distance;
        double lastNearestPoseDistance = 0;
        InternalDistancePoseIndexed nearestPose = nearestPose.path.end();
        for( int poseIndex = i; lastNearestPoseDistance < lookaheadDistance * 2; poseIndex++ ){
            InternalPose pose = path.path.at(i);
            distance = findDistanceBetweenPoses( pose, ipose );
            lastNearestPoseDistance = findDistanceBetweenPoses( nearestPose.path.end(), ipose );
            if( distance < nearestPoses.path.end().distance )
                nearestPose = InternalDistancePoseIndexed{ pose, poseIndex, distance };
        }
    }
    nearestPoses.emplace_back( path.path.at( nearestPose.index ) );
}

PosePath findPath( const std::string &iid ){

}

}//autolib
