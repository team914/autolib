#pragma once
#include "autolib/util/messages.hpp"
#include "okapi/api/control/util/pathfinderUtil.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/pathfinder/include/pathfinder.h"
#include <initializer_list>
#include <vector>
#include <cmath>

namespace autolib{

class PathGenerator{
    public:
    PathGenerator( const okapi::PathfinderLimits &ilimits );

    void generatePath(const std::initializer_list<okapi::Point> &iwaypoints, const std::string &iid);

    void generatePath(  const std::initializer_list<okapi::Point> &iwaypoints, 
                        const std::string &iid,
                        const okapi::PathfinderLimits &ilimits);

    void showPath();
    std::vector<IndexedDistancePosePath> &getPaths();

    protected:
    std::vector<IndexedDistancePosePath> paths;
    std::shared_ptr<okapi::Logger> logger;
    okapi::PathfinderLimits limits;
    std::vector<Point> waypoints;
};
}//autolib
