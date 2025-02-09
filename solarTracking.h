#ifndef SOLARTRACKING_HPP
#define SOLARTRACKING_HPP

#include "time.h"
#include "julianDate.h"
#include "angles.h"
#include <iostream>

using namespace std;

class Sun
{
    private:
        double earthLatitude; // Stored in Degrees
        double earthLongitude; // Positive West Longitude Stored in Degrees

        double apparentLongitude; // Stored in class in Radians
        double correctionOmega; // used to correct equations for apparentLong/RA/Dec
        
        double elipticObliquity; // Stored in Class in Radians
        double obliquityNutation; // Stored in Class in Degrees

        double rightAscension; // Stored in Class in Degrees
        double declinaton; // Stored in Class in Radians

        double localHourAngle; // Stored in Radians

        double altitude; // ouput in Degrees

        double day;
        int year, month;

        double JD; // Julian Date
        double JDE; // Julian Date Ephimeris
        double GMST; // Grenwich Mean Sidreal Time

    public:
        Sun();
        void updateValues();
        void julianAndGrenwich();

        void calcApparentLongitude();
        void calcRightAscension();
        void calcDeclination();
        void calcElipticObliquity();
        void calcObliquityNutation();
        void calcLocalHourAngle();

        void calcAltitude();
        void getAltitude();

        void printDebug();

};

#endif