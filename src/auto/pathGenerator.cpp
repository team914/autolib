#include "autolib/auto/pathGenerator.hpp"

namespace autolib{
/**
 * PathGenerator::PathGenerator 
 * 
 * @param  {PathGenerator::PathGenerator(} undefined : 
 */
PathGenerator::PathGenerator(   const std::initializer_list<Point> &iwaypoints,
                                const okapi::QLength &iminDistanceBetweenPoints){
    std::vector<Point> tempWaypoints = iwaypoints;
    if(tempWaypoints.at(0).x.convert(meter) != 0, tempWaypoints.at(0).y.convert(meter) )
        tempWaypoints.emplace( tempWaypoints.begin(), .00001_mm, .00001_mm );
    for( Point waypoint: tempWaypoints ){
        waypoints.path.emplace_back( waypoint.x.convert(meter), waypoint.y.convert(meter) );
    }
    minDistanceBetweenPoints = iminDistanceBetweenPoints.convert(meter);

    #ifdef DEBUG
        printf("Just ended PathGenerator Waypoints Process\n");
        printf("Now showing you the path generated in points after being converted to meters\n");
        int i=0;
        for (InternalPoint point: waypoints.path){
            printf("\tWayPoint %d:\n",i);
            printf("\t\tx=%+f\n", point.x);
            printf("\t\ty=%+f\n", point.y);
            i++;
        }
    #endif
}

/**
 * PathGenerator 
 * 
 * @param  {PathType} pathType : 
 */
void PathGenerator::generatePath( const PathType &pathType ){
     if( pathType == PathType::HermiteSpline ){
        printf("starting to generate Hermite Spline Path\n");
        InternalPoint currentPoint = waypoints.path.at(0);
        InternalPoint nextPoint = waypoints.path.at(1);
        InternalPoint next2Point = waypoints.path.at(2);
        InternalPoint generatedPoint = currentPoint;
        int pointIndexMax = -1;
        for( InternalPoint point: waypoints.path ){
            pointIndexMax ++;
        }
        #ifdef DEBUG
            printf("Note: pointIndexMax = %d\n", pointIndexMax);
        #endif
        for( int pointIndex = 0; pointIndex <= pointIndexMax; pointIndex++ ){
            if( pointIndex == pointIndexMax - 1 ){
                currentPoint = waypoints.path.at( pointIndex );
                nextPoint = waypoints.path.at( pointIndex );
                next2Point = waypoints.path.at( pointIndex + 1 );
                #ifdef DEBUG
                    printf("Note: pointIndex == pointIndexMax - 1\n");
                #endif
            } else if( pointIndex == pointIndexMax ){
                currentPoint = waypoints.path.at( pointIndex );
                nextPoint = waypoints.path.at( pointIndex );
                next2Point = waypoints.path.at( pointIndex );
                #ifdef DEBUG
                    printf("Note: pointIndex == pointIndexMax\n");
                #endif
            }else{
                currentPoint = waypoints.path.at( pointIndex );
                nextPoint = waypoints.path.at( pointIndex + 1);
                next2Point = waypoints.path.at( pointIndex + 2);
                #ifdef DEBUG
                    printf("Note: pointIndex < pointIndexMax - 1\n");
                #endif
            }
            for( double betweenPointIndex = 0; betweenPointIndex <= 1; betweenPointIndex+=minDistanceBetweenPoints ){
                path.path.emplace_back( generatedPoint );
                generatedPoint = HermiteSplineMath::findNextPoint( betweenPointIndex, currentPoint, nextPoint, nextPoint, next2Point );
                #ifdef DEBUG
                    printf("\tpoint generated between points%d and %d with x = %+f and y = %+f\n", pointIndex, pointIndex + 1 <= waypoints.path.size() ? pointIndex + 1 : pointIndex, generatedPoint.x, generatedPoint.y );
                #endif
            }
        }
    }else if( pathType == PathType::StraightInterpolation ){
        printf("starting to generate a Straight Interpolation Path\n");
        InternalPoint currentPoint = waypoints.path.at(0);
        InternalPoint nextPoint = waypoints.path.at(1);
        InternalPoint generatedPoint = currentPoint;

        for( int pointIndex = 0; pointIndex <= waypoints.path.size(); pointIndex++ ){
            currentPoint = waypoints.path.at( pointIndex );
            nextPoint = waypoints.path.at( pointIndex + 1 <= waypoints.path.size() ? pointIndex + 1 : pointIndex );
            #ifdef DEBUG
                printf("Note: currentPoint = (%f, %f), nextPoint = (%f, %f)\n", currentPoint.x, currentPoint.y, nextPoint.x, nextPoint.y);
            #endif
            generatedPoint = currentPoint;
            while( generatedPoint.x != nextPoint.x && generatedPoint.y != nextPoint.y ){
                path.path.push_back( generatedPoint );
                generatedPoint = StraightInterpolationMath::findNextPoint( generatedPoint, minDistanceBetweenPoints, currentPoint, nextPoint );                
                #ifdef DEBUG
                    printf("\tpoint generated between points%d and %d with x = %f and y = %f\n", pointIndex, pointIndex + 1 <= waypoints.path.size() ? pointIndex + 1 : pointIndex, generatedPoint.x, generatedPoint.y );
                #endif
            }
        }
    }else{
        printf("Note: When creating a path with autolib's PathGenerator, you need to send either PathType::StraightInterpolation or PathType::HermiteSpline\n");
    }
    printf("Successfully Generated Path\n");
}

/**
 * PathGenerator 
 * 
 */
void PathGenerator::showPath(){
    printf("Showing Path\n");
    int pointIndex = 0;
    for( InternalPoint point: path.path ){
        printf("\tPoint%d\n", pointIndex);
        printf("\t\tx = %f\n", point.x);
        printf("\t\ty = %f\n", point.y);
        pointIndex ++;
    }
    printf("Done Showing Path\n");
    printf("Note: If you want to, you can graph this line on desmos.com. For instructions ping me on the unofficial vex discord @potatehoes#7782, or email me acetousk@gmail.com\n");
}

/**
 * PathGenerator 
 * 
 * @return {InternalPath}  : 
 */
InternalPath PathGenerator::getPath(){
    return path;
}

/**
 * PathGenerator 
 * 
 */
void PathGenerator::debugHermiteSpline(){
        InternalPath debugPath;
        debugPath.path.emplace_back( InternalPoint{0,0} );
        debugPath.path.emplace_back( InternalPoint{-1,-1} );
        debugPath.path.emplace_back( InternalPoint{2,0} );
        debugPath.path.emplace_back( InternalPoint{1,1} );

        InternalPoint currentPointDebug = debugPath.path.at(0);
        InternalPoint nextPointDebug = debugPath.path.at(1);
        InternalPoint next2PointDebug = debugPath.path.at(2);
        InternalPoint generatedPoint = currentPointDebug;
        int pointIndexMax = -1;
        for( InternalPoint point: debugPath.path ){
            pointIndexMax ++;
        }
        printf("Note: pointIndexMax = %d\n", pointIndexMax);
        for( int pointIndex = 0; pointIndex <= pointIndexMax; pointIndex++ ){
            if( pointIndex == pointIndexMax - 1 ){
                currentPointDebug = debugPath.path.at( pointIndex );
                nextPointDebug = debugPath.path.at( pointIndex );
                next2PointDebug = debugPath.path.at( pointIndex + 1 );
            } else if( pointIndex == pointIndexMax ){
                currentPointDebug = debugPath.path.at( pointIndex );
                nextPointDebug = debugPath.path.at( pointIndex );
                next2PointDebug = debugPath.path.at( pointIndex );
            }else{
                currentPointDebug = debugPath.path.at( pointIndex );
                nextPointDebug = debugPath.path.at( pointIndex + 1);
                next2PointDebug = debugPath.path.at( pointIndex + 2);
            }
            HermiteSplineMath::debug( minDistanceBetweenPoints, currentPointDebug, nextPointDebug, nextPointDebug, next2PointDebug ); 
        }
        printf("Note: done debugging HermiteSpline\n");
}

}//autolib
