#include <cmath>
#include "Strategy.h"

double Strategy::GetNumUnits(double primaryCount)
{
    double ret = 1.0;
    primaryCount = floor(primaryCount);
    if (primaryCount <= 1)
    {
        ret = 1.0;
    }
    else if (primaryCount <= 2)
    {
        ret = 2.0;
    }
    else if (primaryCount <= 3)
    {
        ret = 4.0;
    }
    else if (primaryCount <= 4)
    {
        ret = 8.0;
    }
    else
    {
        ret = 12.0;
    }

    return ret;
}
