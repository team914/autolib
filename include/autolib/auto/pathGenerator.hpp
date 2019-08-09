#pragma once
#include "autolib/auto/pathGeneratorMath.hpp"
#include "autolib/util/messages.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include <vector>
#include <cmath>

#define DEBUG

namespace autolib{

class PathGenerator{
    public:

    /**
     * This is the constructor for the Path Generator class. To initialize, a list of autolib::Points, and a okapi::QLength
     * value. Each value in the initializer_list is a autolib::Point. For more information on those check out the 
     * autolib/util/messages.hpp file. The next field is the minimum distance between each point generated on the path. 
     * The smaller this value is, the more points will be generated. However, for each point generated it will take 
     * microseconds longer to calculate a path. We suggest a distance roughly equal to 1_mm or 1 millimeter. To use okapi's
     * QLength you send a number such as 1 or 2.3 but after send a _distance ie: 3.471_in. To get a list of these distances,
     * visit: https://pros.cs.purdue.edu/v5/okapi/api/units/index.html 
     * 
     * @param std::initializer_list<Point> &iwaypoints
     *  example: { autolib::Point{ 1_ft, 2_ft }, autolib::Point{ -5_ft, 3_ft } }
     * @param okapi::QLength &iminDistanceBetweenPoints
     *  example: 1_mm
     * 
     */
    PathGenerator(  const std::initializer_list<Point> &iwaypoints,
                    const okapi::QLength &iminDistanceBetweenPoints);

    ~PathGenerator(){}

    /**
     * This enumeration is to tell the generatePath method what kind of path it is generating. The HermiteSplinePath is meant 
     * for smoothing the points on the path, while StraightInterpolation is just filling inbetween the dots. Both methods work,
     * but HermiteSpline is more complicated with a better return while StraightInterpolation is simpler and manageable.
     * 
     * Note: If you don't know what a HermiteSpline and have no intention to learn what it is then use StraightInterpolation,
     * if you want to learn what it is check out the wiki. 
     */
    enum PathType{ HermiteSpline, StraightInterpolation, None };

    /**
     * This method will fill in the points between the waypoints that you generate based off of the PathType that you send. 
     * Currently only HermiteSpline is working.
     * 
     * @param const PathType &pathType
     *  example autolib::PathType::HermiteSpline
     */
    void generatePath( const PathType &pathType );

    /**
     * This will show you the path that is generated. Use the pros terminal to see the points.
     */
    void showPath();

    /**
     * Use this to initialize the Pure Pursuit class.
     * 
     * @return InternalPath path
     *  example: PurePursuit purePursuit( pathGenerator.getPath(), 1_ft );
     */
    InternalPath getPath();

    /**
     * This is a method used for debugging purposes. Use the pros terminal to see the output.
     */
    void debugHermiteSpline();

    protected:
    InternalPath waypoints;
    InternalPath path;
    double minDistanceBetweenPoints;
};
}//autolib
