/*
 * @author D Michael Jones, 914M - acetousk
 * 
 * The ideas portrayed in this code are mainly from the following 
 * documents:
 *      Pure Pursuit            : https://github.com/team914/autolib-pdfs/blob/master/pure-pursuit.pdf
 *      Adaptive Pure Pursuit   : https://github.com/team914/autolib-pdfs/blob/master/adaptive-pure-pursuit.pdf
 *      Path Tracking           : https://github.com/team914/autolib-pdfs/blob/master/path-tracking.pdf
 *      PiLons Position Tracking: https://github.com/team914/autolib-pdfs/blob/master/pilons-position-tracking.pdf
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "autolib/path/purePursuit.hpp"

namespace autolib{

PurePursuit::PurePursuit( const std::vector<IndexedDistancePosePath> &ipaths, const okapi::QLength &ilookaheadDistance ): paths(ipaths){
    std::cout << "\nPure Pursuit: Initializ";
    lookaheadDistance = ilookaheadDistance.convert(meter);
    std::cout << "ed\n";
}

PurePursuitTriangle PurePursuit::run( const okapi::OdomState &ipose, const std::string &iid ){
    okapi::OdomState pose = std::move(ipose);
    return run( Pose{ pose.x, pose.y, pose.theta }, iid );
}

PurePursuitTriangle PurePursuit::run( const Pose &ipose, const std::string &iid ){
    std::cout << "Pure Pursuit: Running\n";
    if( !path.path.empty() ){
        if( path.id != iid )
            findPath( iid );
    }

//    findNearestPose( ipose );
    findGoalPose();
    return findPurePursuitTriangle();
}

void PurePursuit::updateChassis( const double &reqVelocity, const PurePursuitTriangle &itriangle, const std::shared_ptr<OdomChassisController> &controller ){
    std::cout << "Pure Pursuit: Updating Chassis\n";
    PurePursuitTriangle triangle = itriangle;
    double curvature_scales = triangle.localGoalPose.yaw * (controller->getChassisScales().wheelTrack.convert(meter))/2;
    double left = reqVelocity * ( 2 + curvature_scales )/2;
    double right = reqVelocity * ( 2 - curvature_scales )/2;
    controller->getModel()->left( left );
    controller->getModel()->right( right );
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

//bad method?
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
