#ifndef SOLARTRACKING_HPP
#define SOLARTRACKING_HPP

#include "julianDate.h"
#include "time.h"
#include "angles.h"



using namespace std;

class Sun
{
    private:
        double earthLatitude;
        double earthLongitude; // Positive West Longitude

        double apparentLongitude; // Stored in class in Radians
        double correctionOmega; // used to correct equations for apparentLong/RA/Dec
        
        double elipticObliquity; // Stored in Class in Radians
        double obliquityNutation; // Stored in Class in Degrees

        double rightAscension; // Stored in Class in Degrees
        double declinaton; // Stored in Class in Degrees

        double day;
        int year, month;

        double JD; // Julian Date
        double JDE; // Julian Date Ephimeris
        double GMST; // Grenwich Mean Sidreal Time

    public:
        Sun(double, double);
        void updateValues();
        void julianAndGrenwich();

        void calcApparentLongitude();
        void calcRightAscension();
        void calcDeclination();
        void calcElipticObliquity();
        void calcObliquityNutation();

        double meanAnomaly(double);
        double eccentricityOfEarth(double); 
        
        double trueEccentricity();
};

#endif