#ifndef TIME_HPP
#define TIME_HPP

#include "angles.h"
#include <cmath>
#include "ctime"

namespace Time {
    double greenwichMeanSiderealTime(double); // Note - Outputs in Degrees!
    double greenwichApparentSiderealTime(double); // Outputs corrected "apparent" Sidreal Time
    void updateUTC(int&, int&, double&);

    double dynamicUniversalTimeOffset(int, int);

    double dynamicalTime(double, double); 
}
#endif