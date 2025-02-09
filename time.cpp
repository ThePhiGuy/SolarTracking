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

double dynamicUniversalTimeOffset(int year, int month)
{
    // Only an accurate estimate between 2005 and 2050

    double y = year + (month - 0.5)/12; // approx decimal year
    double t = y - 2000;
    double timeDifference = 69.92 + (0.32217 * t) + (0.005589 * pow(t, 2));
    return timeDifference;
}

double dynamicalTime(double julianDate, double universalTime, int year, int month)
{
    double timeDifference = dynamicUniversalTimeOffset(year, month); // gets UT/DT offset

    double dynamicalTime = timeDifference + universalTime; // Universal time in seconds required

    return dynamicalTime; // dynamicaltime (DT) in seconds
}


