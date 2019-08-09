#pragma once
#include "autolib/util/messages.hpp"
#include "autolib/auto/pathGenerator.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/RQuantity.hpp"
#include <memory>
#include <vector>
#include <cmath>
//*

#define DEBUG

namespace autolib{

class PurePursuitMath{
    public:
    /**
     * 
     * @param  {InternalPoint} currentPoint  : 
     * @param  {InternalPath} possiblePoints : 
     * @param  {InternalPath} path           : 
     * @return {InternalPoint}               : 
     */
    static InternalPoint findNearestPoint( const InternalPoint &currentPoint, const InternalPath &possiblePoints, const InternalPath &path);
    
    /**
     * 
     * @param  {InternalPoint} currentPoint : 
     * @param  {InternalPoint} nearestPoint : 
     * @param  {InternalPath} path          : 
     * @param  {double} lookaheadDistance   : 
     * @return {InternalPoint}              : 
     */
    static InternalPoint findGoalPoint( const InternalPoint &currentPoint, const InternalPoint &nearestPoint, const InternalPath &path, const double &lookaheadDistance );

    /**
     * 
     * @param  {InternalPoint} robotPoint : 
     * @param  {InternalPoint} goalPoint  : 
     * @param  {double} robotTheta        : 
     * @return {InternalPoint}            : 
     */
    static InternalPoint convertGlobalToLocalPoints( const InternalPoint &robotPoint, const InternalPoint &goalPoint, const double &robotTheta );

    /**
     * 
     * @param  {InternalPoint} localGoalPoint : 
     * @param  {double} lookaheadDistance     : 
     * @return {Curvature}                    : 
     */
    static Curvature findCurvature( const InternalPoint &localGoalPoint, const double &lookaheadDistance );

    /**
     * 
     * @param  {InternalPoint} currentPoint     : 
     * @param  {InternalPoint} lastNearestPoint : 
     * @param  {InternalPath} path              : 
     * @param  {double} lookaheadDistance       : 
     * @return {InternalPath}                   : 
     */
    static InternalPath findPossiblePoints( const InternalPoint &currentPoint, const InternalPoint &lastNearestPoint, const InternalPath &path, const double &lookaheadDistance );

    /**
     * 
     * @param  {InternalPoint} point       : 
     * @param  {InternalPoint} centerPoint : 
     * @param  {double} lookaheadDistance  : 
     * @return {bool}                      : 
     */
    static bool isPointWithinCircle( const InternalPoint &point, const InternalPoint &centerPoint, const double &lookaheadDistance );

    /**
     * 
     * @param  {InternalPoint} P1 : 
     * @param  {InternalPoint} P2 : 
     * @return {double}           : 
     */
    static double findDistanceBetweenPoints( const InternalPoint &P1, const InternalPoint &P2 );

    /**
     * 
     * @param  {std::vector<double>} list : 
     * @return {double}                   : 
     */
    static double findLowestValue( const std::vector<double> &list );

    /**
     * 
     * @param  {std::vector<double>} list : 
     * @param  {std::vector<int>} pos     : 
     * @return {int}                      : 
     */
    static int findLowestValuePos( const std::vector<double> &list, const std::vector<int> &pos );

    /**
     * 
     * @param  {InternalPoint} currentPoint     : 
     * @param  {InternalPoint} lastNearestPoint : 
     * @param  {InternalPath} path              : 
     * @param  {double} lookaheadDistance       : 
     */
    static void debug( const InternalPoint &currentPoint, const InternalPoint &lastNearestPoint, const InternalPath &path, const double &lookaheadDistance  );
};

}//autolib
