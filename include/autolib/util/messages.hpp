#pragma once
#include "main.h"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/RQuantity.hpp"
#include <initializer_list>
#include <cmath>
#include <vector>

namespace autolib{

struct Pose{
    okapi::QLength x;
    okapi::QLength y;
    okapi::QAngle yaw;
};

struct PurePursuitTriangle{
    InternalPose currentPose;
    InternalPose localGoalPose;
    double l;
    double r;
};

struct InternalPose{
    double x;
    double y;
    double yaw;
};

struct InternalPoseIndexed{
    InternalPose pose;
    int index;
};

struct InternalDistancePoseIndexed{
    InternalPose pose;
    int index;
    double distance;
};

struct PosePath{
    std::string id;
    std::vector<InternalPose> path;
};

struct IndexedPosePath{
    std::string id;
    std::vector<InternalPoseIndexed> path;
};

struct IndexedDistancePosePath{
    std::string id;
    std::vector<InternalDistancePoseIndexed> path;
};

};//autolib
