#include "autolib/auto/pathGenerator.hpp"
#include <initializer_list>
#include <vector>

namespace autolib{

PathGenerator::PathGenerator( const okapi::PathfinderLimits &ilimits ){
    limits = ilimits;

    const std::shared_ptr<okapi::Logger> &ilogger = okapi::Logger::getDefaultLogger();
    logger = ilogger;
}

void PathGenerator::generatePath(const std::initializer_list<Pose> &iwaypoints, const std::string &iid){
    generatePath( iwaypoints, iid, limits );
}

void PathGenerator::generatePath(   const std::initializer_list<Pose> &iwaypoints,
                                    const std::string &iid,
                                    const okapi::PathfinderLimits &ilimits ){
    if (iwaypoints.size() == 0) {
        // No point in generating a path
//        LOG_WARN(std::string(
//        "AsyncMotionProfileController: Not generating a path because no waypoints were given."));
        return;
    }

    std::vector<Waypoint> points;
    points.reserve(iwaypoints.size());
    for (auto &point : iwaypoints) {
        points.push_back(
        Waypoint{point.x.convert(okapi::meter), point.y.convert(meter), point.yaw.convert(radian)});
    }

//    LOG_INFO(std::string("AsyncMotionProfileController: Preparing trajectory"));

    TrajectoryCandidate candidate;
    pathfinder_prepare(points.data(),
                        static_cast<int>(points.size()),
                        FIT_HERMITE_CUBIC,
                        PATHFINDER_SAMPLES_FAST,
                        0.010,
                        ilimits.maxVel,
                        ilimits.maxAccel,
                        ilimits.maxJerk,
                        &candidate);

    const int length = candidate.length;

    if (length < 0) {
        std::string message = "AsyncMotionProfileController: Length was negative. " /*+
                            getPathErrorMessage(points, ipathId, length)*/;

        if (candidate.laptr) {
        free(candidate.laptr);
        }

        if (candidate.saptr) {
        free(candidate.saptr);
        }

//        LOG_ERROR(message);
        throw std::runtime_error(message);
    }

    auto *trajectory = new Segment[length];

    if (trajectory == nullptr) {
        std::string message = "AsyncMotionProfileController: Could not allocate trajectory. " /*+
                            getPathErrorMessage(points, ipathId, length)*/;

        if (candidate.laptr) {
        free(candidate.laptr);
        }

        if (candidate.saptr) {
        free(candidate.saptr);
        }

//        LOG_ERROR(message);
        throw std::runtime_error(message);
    }

//    LOG_INFO(std::string("AsyncMotionProfileController: Generating path"));

    pathfinder_generate(&candidate, trajectory);

//    free(trajectory);

    // Free the old path before overwriting it
//    forceRemovePath(ipathId);

    std::vector<InternalDistancePoseIndexed> poses;
    for( int i = 0; i < candidate.length; i++ ){
        //LOG_INFO(std::string("PathGenerator: Pose Generated") );
        poses.emplace_back( InternalDistancePoseIndexed{ InternalPose{trajectory[i].x, trajectory[i].y, trajectory[i].heading}, candidate.path_length, candidate.totalLength } );
    }
    IndexedDistancePosePath path{ iid,  };

    paths.emplace_back( path );

//    LOG_INFO("AsyncMotionProfileController: Completely done generating path " + ipathId);
//    LOG_DEBUG("AsyncMotionProfileController: Path length: " + std::to_string(length));    
}

void PathGenerator::showPath(){

}

std::vector<IndexedDistancePosePath> &PathGenerator::getPaths(){
    return paths;
}

}//autolib
