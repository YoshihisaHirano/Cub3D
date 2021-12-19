#include "utils.h"

double  angle_in_radians(int angle_in_degrees)
{
    return (angle_in_degrees * ( M_PI / 180.0 ));
}

int bitwise_division(int divident, int divisor)
{
    int  res;
    int  shift;
    
    res = 0;
    shift = 31;
    while (shift > 0) 
    {
        if (divisor << shift <= divident) 
        {
            divident -= divisor << shift;
            res += 1 << shift;
        }
        shift--;
    }
    return (res);
}
