#include "autolib/auto/pathGeneratorMath.hpp"
#include "autolib/util/messages.hpp"

namespace autolib{

/**
 * HermiteSplineMath 
 * 
 * @param  {double} iminLength : 
 * @param  {InternalPoint} P1  : 
 * @param  {InternalPoint} M1  : 
 * @param  {InternalPoint} P2  : 
 * @param  {InternalPoint} M2  : 
 * @return {InternalPoint}     : 
 */
InternalPoint HermiteSplineMath::findNextPoint( const double &iminLength, const InternalPoint &P1, const InternalPoint &M1, const InternalPoint &P2, const InternalPoint &M2 ){
    double x = (P1.x * h00( iminLength )) + (M1.x * h10( iminLength )) + (P2.x * h01( iminLength )) + (M2.x * h11( iminLength ));
    double y = (P1.y * h00( iminLength )) + (M1.y * h10( iminLength )) + (P2.y * h01( iminLength )) + (M2.y * h11( iminLength ));
    return InternalPoint{x,y};
}

/**
 * HermiteSplineMath 
 * 
 * @param  {double} ih00 : 
 * @return {double}      : 
 */
double HermiteSplineMath::h00( const double &ih00 ){
    return (2 * ih00 * ih00 * ih00 ) + ( -3 * ih00 * ih00 ) + 1;
}

/**
 * HermiteSplineMath 
 * 
 * @param  {double} ih10 : 
 * @return {double}      : 
 */
double HermiteSplineMath::h10( const double &ih10 ){
    return ( ih10 * ih10 * ih10 ) + ( -2 * ih10 * ih10 ) + ih10;
}

/**
 * HermiteSplineMath 
 * 
 * @param  {double} ih01 : 
 * @return {double}      : 
 */
double HermiteSplineMath::h01( const double &ih01 ){
    return (-2 * ih01 * ih01 * ih01 ) + ( 3 * ih01 * ih01 );
}

/**
 * HermiteSplineMath 
 * 
 * @param  {double} ih11 : 
 * @return {double}      : 
 */
double HermiteSplineMath::h11( const double &ih11 ){
    return (ih11 * ih11 * ih11 ) + ( -1 * ih11 * ih11 );
}

/**
 * HermiteSplineMath 
 * 
 * @param  {double} iminLength : 
 * @param  {InternalPoint} P1  : 
 * @param  {InternalPoint} M1  : 
 * @param  {InternalPoint} P2  : 
 * @param  {InternalPoint} M2  : 
 */
void HermiteSplineMath::debug( double iminLength, const InternalPoint &P1, const InternalPoint &M1, const InternalPoint &P2, const InternalPoint &M2 ){
    printf("debugging HermiteSplineMath\n");
    printf("\tinitializing Points\n");
    printf("\t\tInternal Point P1: x = %+f, y = %+f\n", P1.x, P1.y);
    printf("\t\tInternal Point P2: x = %+f, y = %+f\n", P2.x, P2.y);
    printf("\t\tInternal Point M1: x = %+f, y = %+f\n", M1.x, M1.y);
    printf("\t\tInternal Point M2: x = %+f, y = %+f\n", M2.x, M2.y);

    double values[5] = { 0, .25, .5, .75, 1 };
    double h00Values[5] = {1, .84375, .5, .15625, 0 };
    double h10Values[5] = {0, .140625, .125, .046875, 0};
    double h01Values[5] = {h00Values[4], h00Values[3], h00Values[2], h00Values[1], h00Values[0] };
    double h11Values[5] = {-h10Values[4], -h10Values[3], -h10Values[2], -h10Values[1], -h10Values[0]};

    int value = 0;
    printf("\thermite functions h00\n");
    for( double h00Value : h00Values ){
        printf("\t\th00(%f) = %f == %f?\n", values[value], h00(values[value]), h00Value );
        value++;
    }
    
    printf("\thermite functions h10\n");
    value = 0;
    for( double h10Value : h10Values ){
        printf("\t\th10(%f) = %f == %f?\n", values[value], h10(values[value]), h10Value );
        value++;
    }

    printf("\thermite functions h01\n");
    value = 0;
    for( double h01Value : h01Values ){
        printf("\t\th01(%f) = %f == %f?\n", values[value], h01(values[value]), h01Value );
        value++;
    }
    

    printf("\thermite functions h11\n");
    value = 0;
    for( double h11Value : h11Values ){
        printf("\t\th11(%f) = %f == %f?\n", values[value], h11(values[value]), h11Value );
        value++;
    }
 
    InternalPoint point{ P1.x, P1.y };
    printf("\trunning hermite spline\n");
    for( double ih = 0; ih <= 1; ih+=iminLength ){
        printf("\t\tPoints x = %+f, y = %+f\n", point.x, point.y);
        point = findNextPoint( ih, P1, M1, P2, M2 );
    }
}

/**
 * StraightInterpolationMath 
 * 
 * @param  {InternalPoint} lastGeneratedPoint : 
 * @param  {double} ixDistanceBetweenPoints   : 
 * @param  {InternalPoint} P1                 : 
 * @param  {InternalPoint} P2                 : 
 * @return {InternalPoint}                    : 
 */
InternalPoint StraightInterpolationMath::findNextPoint( const InternalPoint &lastGeneratedPoint, const double &ixDistanceBetweenPoints, const InternalPoint &P1, const InternalPoint &P2){
    double x = lastGeneratedPoint.x + ( P1.x < P2.x ? ixDistanceBetweenPoints : -ixDistanceBetweenPoints );
    double y = findRise(x,P1,P2);
    if( P2.x <= x && P1.x < P2.x ){
        
        x = P2.x;
        y = P2.y;
    }else if( P2.x >= x && P1.x > P2.x ){

        x = P2.x;
        y = P2.y;        
    }
    return InternalPoint{x,y};
}

/**
 * StraightInterpolationMath 
 * 
 * @param  {double} ixDistanceBetweenPoints : 
 * @param  {InternalPoint} P1               : 
 * @param  {InternalPoint} P2               : 
 * @return {double}                         : 
 */
double StraightInterpolationMath::findRise(const double &ixDistanceBetweenPoints, const InternalPoint &P1, const InternalPoint &P2){
    double x = P2.x-P1.x;//x value of larger triangle
    double y = P2.y-P1.y;//y value of larger triangle
    double ratio = ixDistanceBetweenPoints / x;//ratio between larger triangle and smaller triangle
    return ratio * y;//the y value of smaller triangle
}

}//autolib
