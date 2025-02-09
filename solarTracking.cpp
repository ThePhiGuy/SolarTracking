#include <iostream>
#include "solarTracking.h"

Sun::Sun()
{
    JD = julianDay(2024, 2, 9.01); // Function to pull JD
    JDE = julianEphimerisDay(2024, 2, 9.01);
}

void Sun::obliquityNutation()
{
    double t1 = ((JDE - 2451545) / 36525.0); // EQ 21.1 Julian Epoch Centuries

    double t2 = t1 * t1; // Calculates T^2 and T^3 once, to use multiple times.
    double t3 = t2 * t1;
    
    double meanElongation = 297.85036 + (445267.111480 * t1) - (0.001942 * t2) + (t3 / 189474.0); // Represented as D in nutation eq (p132 meeus)
    double meanSunAnomaly = 357.52772 + (35999.050340 * t1) - (0.0001603 * t2) - (t3 / 300000.0); // Represented as M
    double meanLunarAnomaly = 134.96298 + (477198.867398 * t1) + (0.0086972 * t2) + (t3 / 56250.0); // Represented as M'
    double moonArgumentOfLatitude = 93.27191 + (483202.017538 * t1) - (0.0036825 * t2) + (t3 / 327270.0); // Represented as F
    double moonAscendingNodeLongitude = 125.04452 - (1934.136261 * t1) + (0.0020708 * t2) + (t3 / 450000.0); // Represented as Omega


    double solarMeanLongitude = 280.4665 + (36000.7698 * t1); // Represented by L in Degrees
    double lunarMeanLongitude = 218.3165 + (481267.8813 * t1); // Represented by L' in Degrees

    degreeToRad(solarMeanLongitude); // Converts both values to Radians for trig calculations
    degreeToRad(lunarMeanLongitude);


    nutation = 9.20 * 1;

}



