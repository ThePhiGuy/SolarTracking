#ifndef TIME_HPP
#define TIME_HPP

double greenwichMeanSiderealTime(double); // Note - Outputs in Degrees!
double greenwichApparentSiderealTime(double); // Outputs corrected "apparent" Sidreal Time

double dynamicUniversalTimeOffset(int, int);

double dynamicalTime(double, double); 

#endif