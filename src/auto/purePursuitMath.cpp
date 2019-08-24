#include "autolib/auto/purePursuitMath.hpp"
#include "autolib/util/messages.hpp"
/*
namespace autolib{

InternalPoint PurePursuitMath::findNearestPoint( const InternalPoint &currentPoint, const InternalPath &possiblePoints, const InternalPath &path){

    std::vector<int> pos;
    std::vector<double> distance;

    for( InternalPoint point: possiblePoints.path ){
        pos.push_back( point.pos );
        distance.push_back( findDistanceBetweenPoints( point, currentPoint ) );
    }
    int lowestDistancePos = findLowestValuePos( distance, pos );
    #ifdef DEBUG
        printf("nearestPoint = (%f, %f)\n", path.path.at(lowestDistancePos).x, path.path.at(lowestDistancePos).y );
    #endif
    return path.path.at(lowestDistancePos);
}
InternalPoint PurePursuitMath::findGoalPoint( const InternalPoint &currentPoint, const InternalPoint &nearestPoint, const InternalPath &path, const double &lookaheadDistance ){
    InternalPoint goalPoint = currentPoint;
    int maxPointIndex = -1;
    for( InternalPoint point: path.path ){
        maxPointIndex++;
    }
    #ifdef DEBUG
        int goalCount = 0;
    #endif
    double maxValue = 100;
    for( int pointIndex = nearestPoint.pos; pointIndex <= maxPointIndex; pointIndex ++ ){
        InternalPoint point = path.path.at(pointIndex);
        double value = okapi::ipow( ( point.x - currentPoint.x ), 2) + okapi::ipow( (point.y - currentPoint.y), 2 );
        double imaxValue = std::abs(lookaheadDistance - value);
        #ifdef DEBUG
            printf("\tstd::abs(lookaheadDistance(%f) - value(%f)) ((%f)) < maxValue(%f)\n", lookaheadDistance, value, imaxValue, maxValue);
        #endif
        if( imaxValue < maxValue ? true : false ){
            maxValue = imaxValue;
            #ifdef DEBUG
                goalCount++;
                printf("Intermittent Goal Point = (%f, %f, %d)\n", goalPoint.x, goalPoint.y, goalPoint.pos);
                printf("\tdistance between currentPoint(%f, %f) and goalPoint(%f, %f) ((%f))\n", currentPoint.x, currentPoint.y, goalPoint.x, goalPoint.y, findDistanceBetweenPoints(currentPoint, goalPoint));
            #endif
            goalPoint = point;
        }
    }
    printf("Goal Point = (%f, %f, %d)\n", goalPoint.x, goalPoint.y, goalPoint.pos);
    #ifdef DEBUG
        printf("\tdistance between currentPoint(%f, %f) and goalPoint(%f, %f) ((%f)), maxValue(%f), number of Intermittent goalPoints = %d\n", currentPoint.x, currentPoint.y, goalPoint.x, goalPoint.y, findDistanceBetweenPoints(currentPoint, goalPoint), maxValue, goalCount);
    #endif
    return goalPoint;
}
InternalPoint PurePursuitMath::convertGlobalToLocalPoints( const InternalPoint &robotPoint, const InternalPoint &goalPoint, const double &robotTheta ){
    double sinTheta = std::sin( robotTheta );
    double cosTheta = std::cos( robotTheta );
    double xDif = ( goalPoint.x - robotPoint.x );
    double yDif = ( goalPoint.y - robotPoint.y );
    double x = xDif * cosTheta + yDif * sinTheta;
    double y = -xDif * sinTheta + yDif * cosTheta;
    #ifdef DEBUG
        printf("convert Global to Local Points sin(%f), cos(%f), xDif(%f), yDif(%f), (%f, %f)\n", sinTheta, cosTheta, xDif, yDif, x, y);
    #endif
    return InternalPoint{x,y};
}
Curvature PurePursuitMath::findCurvature( const InternalPoint &localGoalPoint, const double &lookaheadDistance ){
    double iyaw = (2 * localGoalPoint.x) / okapi::ipow( lookaheadDistance, 2 );
    double idistance = okapi::ipow(lookaheadDistance, 2) / (2 * localGoalPoint.x);
    #ifdef DEBUG
        printf("findCurvature\n\tiyaw(%f), idistance(%f)\n", iyaw, idistance);
    #endif
    return Curvature{ iyaw, idistance };
}
InternalPath PurePursuitMath::findPossiblePoints( const InternalPoint &currentPoint, const InternalPoint &lastNearestPoint, const InternalPath &path, const double &lookaheadDistance ){
    InternalPath possiblePoints;
    int maxPointIndex = -1;
    for( InternalPoint point: path.path ){
        maxPointIndex++;
    }
    #ifdef DEBUG
        printf("Now Debugging FindPossiblePoints\n");
        printf("\tmaxPointIndex = %d\n", maxPointIndex);
    #endif
    for( int pointIndex = lastNearestPoint.pos; pointIndex <= maxPointIndex; pointIndex+=1/*This shouldn't be .5 but otherwise it skips a number. I have no idea why... */// ){
/*
        if( pointIndex == -1 ){
            pointIndex = 0;
        }
        InternalPoint point = path.path.at(pointIndex);//hopefully this doesn't throw an error when nearestPoint.pos == -1
        #ifdef DEBUG
            printf( "\t\tInspecting Point (%f, %f, %d)\n", point.x, point.y, pointIndex );
        #endif
        if( isPointWithinCircle( point, currentPoint, lookaheadDistance ) ){
            possiblePoints.path.emplace_back( point.x, point.y, point.pos );
            #ifdef DEBUG
                printf("\tNew Point added to Possible Points (%f, %f, %d )", point.x, point.y, point.pos);
            #endif
        }
        printf("\t%d <= %d\n", pointIndex, maxPointIndex);
    }
    return possiblePoints;
}
bool PurePursuitMath::isPointWithinCircle( const InternalPoint &point, const InternalPoint &centerPoint, const double &lookaheadDistance ){
    bool output = okapi::ipow( ( point.x - centerPoint.x ), 2) + okapi::ipow( point.y - centerPoint.y, 2 ) <= okapi::ipow( lookaheadDistance, 2 );
    #ifdef DEBUG
        printf("\t\tIs Point Within Circle?\n");
        printf("\t\t\t (point.x(%f) - centerPoint.x(%f))^2 + ( point.y(%f) - centerPoint.y(%f) )^2 <= lookaheadDistance(%f) ? %d \n\n", point.x, centerPoint.x, point.y, centerPoint.y, lookaheadDistance, output );
    #endif
    //(point.x - centerPoint.x)^2 + (point.y - centerPoint.y)^2 <= lookaheadDistance^2;
    return output;
}
double PurePursuitMath::findDistanceBetweenPoints( const InternalPoint &P1, const InternalPoint &P2 ){
    return std::sqrt( okapi::ipow( P2.x - P1.x, 2 ) + okapi::ipow( P2.y - P1.y, 2 ) );
}
double PurePursuitMath::findLowestValue( const std::vector<double> &list ){
    double lowestValue = 5;//5 meters should be wayyy too high of a number in vex
    for( double value: list ){
        if( value < lowestValue )
            lowestValue = value;
    }
    return lowestValue;
} 
int PurePursuitMath::findLowestValuePos( const std::vector<double> &list, const std::vector<int> &pos ){
    double lowestValue = findLowestValue( list );
    int b;
    for( int i = 0; i<= list.max_size(); i++ ){
        if(list.at(i) == lowestValue){
            b = i;
            i = list.max_size() + 1;
        }
    }
    return pos.at(b);
}
void PurePursuitMath::debug( const InternalPoint &currentPoint, const InternalPoint &lastNearestPoint, const InternalPath &path, const double &lookaheadDistance  ){
    printf("Now Debugging PurePursuitMath\n");
    printf("\tCurrentPoint = (%f, %f)\n", currentPoint.x, currentPoint.y);
    printf("\tlastNearestpoint = (%f, %f)\n", lastNearestPoint.x, lastNearestPoint.y);
    printf("\tlookaheadDistance = %f\n", lookaheadDistance);
    printf("\tlastNearestPoint.pos = %d\n", lastNearestPoint.pos);

    InternalPath possiblePoints = findPossiblePoints( currentPoint, lastNearestPoint, path, lookaheadDistance );

    std::vector<int> pos;
    std::vector<double> distance;

    for( InternalPoint point: possiblePoints.path ){
        printf("\t\tpoint.pos = %d", pos.back() );
        printf("\tdistanceBetweenpoints = %f\n", distance.back() );
        pos.push_back( point.pos );
        distance.push_back( findDistanceBetweenPoints( point, currentPoint ) );
    }

    int lowestDistancePos = findLowestValuePos( distance, pos );
    printf("the closet point = (%f, %f, %d)\n", path.path.at(lowestDistancePos).x, path.path.at(lowestDistancePos).y, lowestDistancePos );

}
}//autolib
//*/
