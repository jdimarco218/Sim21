#include "Strategy.h"

double Strategy::GetNumUnits(int primaryCount)
{
    double ret = 1.0;
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
