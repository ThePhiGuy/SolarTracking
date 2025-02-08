#include <iostream>
#include <iomanip>
#include "julianDate.h"
#include "greenwichTime.h"
#include "angles.h"

using namespace std;

int main()
{
    double testJD = 2446896.30625;
    double GMST = greenwichMeanSiderealTime(testJD);
    double seconds;
    int hour, minutes;
    double decimalDegrees;

    hour = 8;
    minutes = 34;
    seconds = 57.0896;

    HMStoDecimal(hour, minutes, seconds, decimalDegrees);
    cout << "\n" << decimalDegrees << endl;

    return 0;
}