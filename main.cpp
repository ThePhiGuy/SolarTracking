#include <iostream>
#include <iomanip>

#include "solarTracking.h"

using namespace std;

int main()
{
    Sun solarTest;

    solarTest.updateValues();
    solarTest.getAltitude();

    solarTest.printDebug();

    return 0;
}