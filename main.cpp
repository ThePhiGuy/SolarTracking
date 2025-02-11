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

        latitude = testLat[1];
        longitude = testLong[1];

    }

    Sun solarTest(latitude, longitude);

    
    double day = 11.0;
    ofstream testfile("out.txt");
    for (int i = 0; i < 101; i++)
    {
        day += .01;
        testfile << solarTest.customTimeUpdate(2025, 10, day);
    }

    return 0;
}