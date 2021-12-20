#include "utils.h"

double  angle_in_radians(int angle_in_degrees)
{
    return (angle_in_degrees * ( M_PI / 180.0 ));
}

int divide_nums(double divident, double divisor)
{
    // printf("%d divident, %d - divisor\n", divident, divisor);
    if (divisor == 0) {
        printf("zero division\n");
        divisor = 0.1;
    }
    return (int)(floor(divident / divisor));
}

// find ways to make it work!!!
int bitwise_division(int divident, int divisor)
{
    int  res;
    int  shift;
    
    res = 0;
    shift = 31;
    while (shift > 0) 
    {
        if ((divisor << shift) <= divident)
        {
            printf("%d - divisor\n", divisor);
            divident -= (divisor << shift);
            res += (1 << shift);
            printf("%d - shift, %d - res, %d - divident\n", shift, res, divident);
        }
        shift--;
    }
    return (res);
}
