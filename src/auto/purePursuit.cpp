#include "autolib/auto/purePursuit.hpp"

namespace autolib{

/**
 * PurePursuit::PurePursuit 
 * 
 * @param  {InternalPath} iipath               : 
 * @param  {okapi::QLength} ilookaheadDistance : 
 */
PurePursuit::PurePursuit( const std::vector<IndexedDistancePosePath> &ipaths, const okapi::QLength &ilookaheadDistance ): paths(ipaths){
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
PurePursuitTriangle PurePursuit::getGoalCurvature( const Pose &ipose, const std::string &iid ){
    if( !path.path.empty() ){
        if( path.id != iid )
            findPath( iid );
    }

    findNearestPose( ipose );
    findGoalPose();
    return findPurePursuitTriangle();
}

void PurePursuit::findPath( const std::string &iid ){
    for( const auto &ipath: paths ){
        if( ipath.id == iid ){
            avgDistanceBetweenPoses = ipath.path.front().index / ipath.path.front().distance;
            path.id = iid;
            for( const auto &pose: ipath.path ){
                path.path.emplace_back( pose );
            }
        }
    }
}

double PurePursuit::findDistanceBetweenPoses( const InternalPose &P1, const InternalPose &P2 ){
    return std::sqrt( okapi::ipow( P2.x - P1.x, 2 ) + okapi::ipow( P2.y - P1.y, 2 ) );
}

void PurePursuit::findNearestPose( const Pose &iipose ){
    InternalPose ipose{ iipose.x.convert(meter), iipose.y.convert(meter), iipose.yaw.convert(radian) };
    if( currentPoses.path.empty() )
        currentPoses.id = std::string("currentPoses");
    currentPoses.path.emplace_back( ipose );
    double maxDistance;

    if( nearestPoses.path.empty() ){
        nearestPoses.id = std::string("nearestPoses");
        maxDistance = findDistanceBetweenPoses( path.path.front().pose, path.path.back().pose );
        nearestPoses.path.emplace_back( InternalDistancePoseIndexed{ path.path.front().pose, 0, 
                findDistanceBetweenPoses( path.path.front().pose, ipose ) } );
    }else
        maxDistance = lookaheadDistance * 2;
    
    double distance = findDistanceBetweenPoses( nearestPoses.path.back().pose, ipose );
    double lastNearestPoseDistance = 0;

    for( int poseIndex =  nearestPoses.path.at( nearestPoses.path.size() -1 ).index; lastNearestPoseDistance < maxDistance; poseIndex++ ){
        InternalPose pose = path.path.at(poseIndex).pose;
        distance = findDistanceBetweenPoses( pose, ipose );
        lastNearestPoseDistance = findDistanceBetweenPoses(  nearestPoses.path.back().pose, ipose );
        if( distance <  nearestPoses.path.back().distance )
            nearestPoses.path.push_back( InternalDistancePoseIndexed{ pose, poseIndex, distance } );
    }
}

void PurePursuit::findGoalPose(){
    double distance = nearestPoses.path.at( nearestPoses.path.size() -1 ).distance;
    double lastNearestPoseDistance = 0;

    double minRadius = lookaheadDistance - ( avgDistanceBetweenPoses / 2 );
    double maxRadius = minRadius + avgDistanceBetweenPoses;

    for( int poseIndex = nearestPoses.path.at( nearestPoses.path.size() - 1 ).index; distance < lastNearestPoseDistance; poseIndex++ ){
        InternalPose pose = path.path.at(poseIndex).pose;
        distance = findDistanceBetweenPoses( pose, currentPoses.path.back() );
        lastNearestPoseDistance = findDistanceBetweenPoses(  nearestPoses.path.back().pose, pose );
        if( minRadius <= distance <= maxRadius )
            if( goalPoses.path.empty() )
                goalPoses.id = std::string("goalPoses");
            goalPoses.path.push_back( InternalPoseIndexed{ pose, poseIndex} );
    }
}

PurePursuitTriangle PurePursuit::findPurePursuitTriangle(){
    double yaw = currentPoses.path.back().yaw;
    double sinYaw = std::sin( yaw );
    double cosYaw = std::cos( yaw );

    InternalPose dif{ ( goalPoses.path.back().pose.x - currentPoses.path.back().x ), ( goalPoses.path.back().pose.y - currentPoses.path.back().y ), yaw };

    InternalPose currentPose{ 0,0, yaw };
    InternalPose localGoalPose{
        ( dif.x * cosYaw ) + ( dif.y * sinYaw ),
        ( -dif.x * sinYaw ) + ( dif.y * cosYaw ),
        yaw
    };
    double l(okapi::ipow(lookaheadDistance, 2));
    PurePursuitTriangle triangle{
        currentPose,
        localGoalPose,
        l,
        l / ( 2 * localGoalPose.x )
    };


    triangles.emplace_back(
        triangle
    );
    return triangle;
}

}//autolib
