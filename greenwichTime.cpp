#include "greenwichTime.h"

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
