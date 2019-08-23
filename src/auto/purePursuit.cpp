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
    findNearestPose( ipose );
    findGoalPose();
    convertGlobalToLocalPose();
    return findCurvature();
}

void PurePursuit::findNearestPose( const InternalPose &ipose ){
    currentPose.path.emplace_back( ipose );
    if( !nearestPoses.path.empty() ){
        
    }
}

}//autolib
