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
struct Point{
    Point(const okapi::QLength &ix, const okapi::QLength &iy):x(ix), y(iy){}
    okapi::QLength x;
    okapi::QLength y;
};

struct Path{
    Path(){}
    std::vector<Point> path;
};

struct Curvature{
    double yaw;
    double distance;
};

//These are only meant for internal uses. Do not use these unless you are an expert.
struct InternalPoint{
    InternalPoint( double ix, double iy, int ipos = -1 ) : x(ix), y(iy), pos(ipos) {}
    double x;
    double y;
    int pos = -1;
};

struct InternalPath{
    std::vector<InternalPoint> path;
};


};//autolib
