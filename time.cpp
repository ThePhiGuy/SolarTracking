#include "time.h"
#include "angles.h"
#include <cmath>

using namespace std;

double greenwichMeanSiderealTime(double julianDate)
{
    double julianCenturies = (julianDate - 2451545.0) / 36525;

    double meanSidereal = 280.46061837 + (360.98564736629 * (julianDate - 2451545.0)) + (0.000387933 * pow(julianCenturies, 2)) - (pow(julianCenturies, 3) / 38710000);
    
    simplifyDegrees(meanSidereal);

    return (meanSidereal); // OUTPUT IN DEGREES!! Input Julian Date of current UT time.
}

double greenwichApparentSiderealTime(double greenwichMeanSidreal)
{
    // @TODO : Implement Apparent Sidereal Time accounting for Nutation
    return 0.0;
}

inline double dynamicUniversalTimeOffset(double julianDate)
{
    double julianCenturies = (julianDate - 2451545.0) / 36525;
    double timeDifference = 102.3 + (123.5 * julianCenturies) + (32.5 * pow(julianCenturies, 2)); // offset = TD - UT
    return timeDifference;
}

double dynamicalTime(double julianDate, double universalTime)
{
    double timeDifference = dynamicUniversalTimeOffset(julianDate); // gets offset from other function

    double dynamicalTime = timeDifference + universalTime; // Universal time in seconds required

    return dynamicalTime; // dynamicaltime (DT) in seconds
}


