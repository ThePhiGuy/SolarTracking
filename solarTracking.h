#ifndef SOLARTRACKING_HPP
#define SOLARTRACKING_HPP

#include "julianDate.h"
#include "time.h"
#include "angles.h"



using namespace std;

class Sun
{
    private:
        double meanAnomaly;
        double geometricMeanLongitude; // AKA mean equinox of the date
        double earthOrbitEccentricity;
        double eclipticOblicquity; // EQ 21.2
        double nutation; // EQ 21.1
        double JD;
        double JDE;
    public:
        Sun();
        double meanAnomaly(double);
        double geometricMeanLongitude(double);
        double eccentricityOfEarth(double); 
        void obliquityNutation();
        double trueEccentricity();
        void elipticObliquity();
};

#endif