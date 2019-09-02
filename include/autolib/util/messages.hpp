/*
 * @author D Michael Jones, 914M - acetousk
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
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

struct InternalPose{
    double x;
    double y;
    double yaw;
};

struct PurePursuitTriangle{
    InternalPose currentPose;
    InternalPose localGoalPose;
    double l;
    double r;
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
