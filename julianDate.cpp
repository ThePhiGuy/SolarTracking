#include "julianDate.h"

using namespace std;

double julianDay(int year, int month, double day)
{
    if ((month == 1) || (month == 2)) // If date in Jan or Feb, it is the 13th/14th month of previous year
    {
        year -= 1;
        month += 12;
    }

    int intermediateB = -13; // Good for all values on gregorian calendar from 1900 March 1 to 2100 Feb 28;

    double julianDay = (int)(365.25 * (year + 4716)) + (int)(30.6001 * (month + 1)) + day + intermediateB - 1524.5;

    return julianDay;
}


inline double julianToModified(double julianDate)
{
    return (julianDate - 2400000.5); 
}

double julianEphimerisDay(int year, int month, double day)
{
    double julian = julianDay(year, month, day);

    double offset = Time::dynamicUniversalTimeOffset(year, month);

    return (julian + offset);
}
