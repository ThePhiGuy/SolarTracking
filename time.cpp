#include "time.h"

double Time::greenwichMeanSiderealTime(double julianDate)
{
    double julianCenturies = (julianDate - 2451545.0) / 36525;

    double meanSidereal = 280.46061837 + (360.98564736629 * (julianDate - 2451545.0)) + (0.000387933 * pow(julianCenturies, 2)) - (pow(julianCenturies, 3) / 38710000);
    
    simplifyDegrees(meanSidereal);

    return (meanSidereal); // OUTPUT IN DEGREES!! Input Julian Date of current UT time.
}

double Time::greenwichApparentSiderealTime(double greenwichMeanSidreal)
{
    // @TODO : Implement Apparent Sidereal Time accounting for Nutation
    return 0.0;
}

/**
 * @brief Update yr, month, and day for Julian time in utc
 * 
 * @param yr Will be updated with year since the epoch
 * @param mo Month of the current year
 * @param day Will be set to the fractional day in UTC
 */
void Time::updateUTC(int &yr, int &mo, double &day) {
    std::time_t *currentTime = new std::time_t();
    std::time(currentTime);
    std::tm *gm = gmtime(currentTime);
    yr = gm->tm_year + 1900;
    mo = gm->tm_mon + 1;
    day = gm->tm_mday + (gm->tm_min*60 + gm->tm_hour*3600)/86400.0;
    // yr = 1992;
    // mo = 10;
    // day = 13.0;
}

double Time::dynamicUniversalTimeOffset(int year, int month)
{
    // Only an accurate estimate between 2005 and 2050

    double y = year + (month - 0.5)/12; // approx decimal year
    double t = y - 2000;
    double timeDifference = 69.92 + (0.32217 * t) + (0.005589 * pow(t, 2));
    return timeDifference;
}

double Time::dynamicalTime(double julianDate, double universalTime, int year, int month)
{
    double timeDifference = dynamicUniversalTimeOffset(year, month); // gets UT/DT offset

    double dynamicalTime = timeDifference + universalTime; // Universal time in seconds required

    return dynamicalTime; // dynamicaltime (DT) in seconds
}


