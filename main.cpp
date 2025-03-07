#include <iostream>
#include <iomanip>

#include "solarTracking.h"

using namespace std;

int main()
{
    bool debug = true;
    double latitude, longitude;
    if (!debug) 
    {
        cout << "\nplease enter a latitude and longitude (west positive)\nLatitude:";
        cin >> latitude;
        cout << "\nLongitude: ";
        cin >> longitude;
    }
    else
    {
        double testLong[4] = {85.5815, 46.731705};
        double testLat[4] = {42.9328, 117.00002};

        latitude = testLat[0];
        longitude = testLong[0];

    }

    Sun solarTest(latitude, longitude);

    solarTest.getSlope();

    return 0;
}