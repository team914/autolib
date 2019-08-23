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

struct Curvature{
    double yaw;
    double distance;
};

//This is depricated and is going to be deleted in version 1.0.0
struct Pose{
    okapi::QLength x;
    okapi::QLength y;
    okapi::QAngle yaw;
};

//These are only meant for internal uses. Do not use these unless you are an expert.
struct InternalPoint{
    InternalPoint( const double &ix, const double &iy) : x(ix), y(iy) {}
    double x;
    double y;
};

struct InternalPointIndexed: public InternalPoint{
    InternalPointIndexed( const InternalPoint &ipoint, const int &iindex ): point(ipoint), index(iindex){}
    InternalPoint point;
    int index;
};

struct InternalDistancePointIndexed: public InternalPoint{
    InternalDistancePointIndexed( const InternalPoint &ipoint, const int &iindex, const double &idistance ): 
            point(ipoint), index(iindex), distance(idistance){}
    InternalPoint point;
    int index;
    double distance;
};

struct InternalPose: public InternalPoint{
    InternalPose( double ix, double iy, double iyaw ): InternalPoint(ix, iy), yaw(iyaw){}
    double yaw;
};

struct InternalPoseIndexed: public InternalPose{
    InternalPoseIndexed( const InternalPose &ipose, const int &iindex ): pose(ipose), index(iindex){}
    InternalPose pose;
    int index;
};

struct InternalDistancePoseIndexed: public InternalPose{
    InternalDistancePoseIndexed( const InternalPose &ipose, const int &iindex, const double &idistance ): 
            pose(ipose), index(iindex), distance(idistance){}    
    InternalPose pose;
    int index;
    double distance;
};

struct InternalDistancePointIndexed: public InternalPoint{
    InternalDistancePointIndexed( const InternalPoint &ipoint, const int &iindex, const double &idistance ): 
            point(ipoint), index(iindex), distance(idistance){}
    InternalPoint point;
    int index;
    double distance;
};

struct PosePath{
    std::string id;
    std::vector<InternalPose> path;
};

//This is depricated and is going to be deleted in version 1.0.0
struct InternalPath{
    std::vector<InternalPoint> path;
};

};//autolib
