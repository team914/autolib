/*
 * @author D Michael Jones, 914M - acetousk
 * @author Ryan Benasutti, WPI - Octogonapus
 * 
 * The ideas portrayed in this code are mainly from the following 
 * documents:
 *      Pure Pursuit: https://github.com/team914/autolib-pdfs/blob/master/pure-pursuit.pdf
 *      Pathfinder  : https://github.com/JacisNonsense/Pathfinder/issues
 *      Desmos      : https://www.desmos.com/calculator/bulcgjwydy
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
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
    /**
     * PathGenerator class constructor
     * 
     * @param  {okapi::PathfinderLimits} ilimits : 
     */
    PathGenerator( const okapi::PathfinderLimits &ilimits );
    
    /**
     * generatePath will simply generate a path. It generates a path via a Hermite Spline.
     * For more information about what a Hermite Spline is and what it does see: 
     *      Pathfinder  : https://github.com/JacisNonsense/Pathfinder/issues
     *      Desmos      : https://www.desmos.com/calculator/bulcgjwydy
     * 
     * @param  {std::initializer_list<Pose>} iwaypoints : 
     * @param  {std::string} iid                        : 
     */
    void generatePath(const std::initializer_list<Pose> &iwaypoints, const std::string &iid);

    /**
     * generatePath will simply generate a path. It generates a path via a Hermite Spline.
     * For more information about what a Hermite Spline is and what it does see: 
     *      Pathfinder  : https://github.com/JacisNonsense/Pathfinder/issues
     *      Desmos      : https://www.desmos.com/calculator/bulcgjwydy
     * 
     * @param  {std::initializer_list<Pose>} iwaypoints : 
     * @param  {std::string} iid                        : 
     * @param  {okapi::PathfinderLimits} ilimits        : 
     */
    void generatePath(  const std::initializer_list<Pose> &iwaypoints, 
                        const std::string &iid,
                        const okapi::PathfinderLimits &ilimits);
    /**
     * This will show the path in the PROS Terminal. Willing to accept PRs for showing the 
     * path on the brain's screen.
     */
    void showPath();
    
    /**
     * This is used to get the paths. It should be used to initialize the PurePursuit class.
     * 
     * @return {std::vector<IndexedDistancePosePath>}  : 
     */
    std::vector<IndexedDistancePosePath> &getPaths();

    protected:
    std::vector<IndexedDistancePosePath> paths;
    std::shared_ptr<okapi::Logger> logger;
    okapi::PathfinderLimits limits;
    std::vector<Point> waypoints;
};
}//autolib
