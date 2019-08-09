#include "autolib/auto/purePursuit.hpp"

namespace autolib{

/**
 * PurePursuit::PurePursuit 
 * 
 * @param  {InternalPath} iipath               : 
 * @param  {okapi::QLength} ilookaheadDistance : 
 */
PurePursuit::PurePursuit( const InternalPath &iipath, const okapi::QLength &ilookaheadDistance ){
    #ifdef DEBUG
        printf( "\tInheriting Points from Path\n" );
    #endif
    InternalPath ipath = iipath;
    int pointIndex = 0;
    for( InternalPoint point: ipath.path ){
        point = InternalPoint{ point.x, point.y, pointIndex };
        path.path.emplace_back( point );
        pointIndex ++;
        #ifdef DEBUG
            printf( "\tnew Point (%+f, %+f, %d)\n", point.x, point.y, pointIndex );
        #endif
    }
    lookaheadDistance = ilookaheadDistance.convert(meter);
}

/**
 * PurePursuit 
 * 
 * @param  {okapi::QLength} ix    : 
 * @param  {okapi::QLength} iy    : 
 * @param  {okapi::QAngle} itheta : 
 * @return {Curvature}            : 
 */
Curvature PurePursuit::getGoalCurvature( const okapi::QLength &ix , const okapi::QLength &iy, const okapi::QAngle &itheta ){
    theta = itheta.convert(radian);
    currentPoint = InternalPoint{ ix.convert(meter), iy.convert(meter) };
    lastNearestPoint = nearestPoint;
    nearestPoint = getNearestPoint( ix, iy );
    goalPoint = PurePursuitMath::findGoalPoint( currentPoint, nearestPoint, path, lookaheadDistance );
    localGoalPoint = PurePursuitMath::convertGlobalToLocalPoints( currentPoint, goalPoint, theta );
    return PurePursuitMath::findCurvature( localGoalPoint, lookaheadDistance );
}

/**
 * PurePursuit 
 * 
 * @param  {okapi::QLength} ix : 
 * @param  {okapi::QLength} iy : 
 * @return {InternalPoint}     : 
 */
InternalPoint PurePursuit::getNearestPoint( const okapi::QLength &ix , const okapi::QLength &iy ){        
 
    #ifdef DEBUG
        printf("Now finding Nearest Point");
        PurePursuitMath::debug( currentPoint, lastNearestPoint, path, lookaheadDistance );
    #endif

    possiblePoints = PurePursuitMath::findPossiblePoints( currentPoint, lastNearestPoint, path, lookaheadDistance );
    return PurePursuitMath::findNearestPoint(  currentPoint, possiblePoints, path );
}

}//autolib
