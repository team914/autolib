#pragma once
#include "autolib/util/messages.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include <vector>
#include <cmath>

#define DEBUG

namespace autolib{

class HermiteSplineMath{
    public:
    /**
     * 
     * @param  {double} iminLength : 
     * @param  {InternalPoint} P1  : 
     * @param  {InternalPoint} M1  : 
     * @param  {InternalPoint} P2  : 
     * @param  {InternalPoint} M2  : 
     * @return {InternalPoint}     : 
     */
    static InternalPoint findNextPoint( const double &iminLength, const InternalPoint &P1, const InternalPoint &M1, const InternalPoint &P2, const InternalPoint &M2 );
    /**
     * 
     * @param  {double} ih00 : 
     * @return {double}      : 
     */
    static double h00( const double &ih00 );
    /**
     * 
     * @param  {double} ih10 : 
     * @return {double}      : 
     */
    static double h10( const double &ih10 );
    /**
     * 
     * @param  {double} ih01 : 
     * @return {double}      : 
     */
    static double h01( const double &ih01 );
    /**
     * 
     * @param  {double} ih11 : 
     * @return {double}      : 
     */
    static double h11( const double &ih11 );
    /**
     * 
     * @param  {double} iminLength : 
     * @param  {InternalPoint} P1  : 
     * @param  {InternalPoint} M1  : 
     * @param  {InternalPoint} P2  : 
     * @param  {InternalPoint} M2  : 
     */
    static void debug( double iminLength, const InternalPoint &P1, const InternalPoint &M1, const InternalPoint &P2, const InternalPoint &M2 );
};

class StraightInterpolationMath{
    public:
    /**
     * 
     * @param  {InternalPoint} lastGeneratedPoint : 
     * @param  {double} ixDistanceBetweenPoints   : 
     * @param  {InternalPoint} P1                 : 
     * @param  {InternalPoint} P2                 : 
     * @return {InternalPoint}                    : 
     */
    static InternalPoint findNextPoint( const InternalPoint &lastGeneratedPoint, const double &ixDistanceBetweenPoints, const InternalPoint &P1, const InternalPoint &P2);
    /**
     * 
     * @param  {double} ixDistanceBetweenPoints : 
     * @param  {InternalPoint} P1               : 
     * @param  {InternalPoint} P2               : 
     * @return {double}                         : 
     */
    static double findRise(const double &ixDistanceBetweenPoints, const InternalPoint &P1, const InternalPoint &P2);
    
};

}//autolib
