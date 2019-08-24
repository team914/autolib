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

//Please get to know these. They are meant for communication between the various classes of autolib

//This is depricated and is going to be deleted in version 1.0.0
struct Point{
    Point(const okapi::QLength &ix, const okapi::QLength &iy):x(ix), y(iy){}
    okapi::QLength x;
    okapi::QLength y;
};

//This is depricated and is going to be deleted in version 1.0.0
struct Path{
    Path(){}
    std::vector<Point> path;
};

struct Pose{
    okapi::QLength x;
    okapi::QLength y;
    okapi::QAngle yaw;
};

struct InternalPoint{
    double x;
    double y;
};

struct InternalPath{
    std::vector<InternalPoint> path;
};
//up til here

struct Curvature{
    double yaw;
    double distance;
};



//This is depricated and is going to be deleted in version 1.0.0


//These are only meant for internal uses. Do not use these unless you are an expert.
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

/**
 * This will be needed in the future
 */
/*
struct InternalPoint{
    double x;
    double y;
};

struct InternalPointIndexed{
    InternalPoint point;
    int index;
};

struct InternalDistancePointIndexed{
    InternalPoint point;
    int index;
    double distance;
};


struct PointPath{
    std::string id;
    std::vector<InternalPoint> path;
};
//*/

};//autolib
