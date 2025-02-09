#include <iostream>
#include <iomanip>

#include "solarTracking.h"

using namespace Time;

int main()
{
    double test = dynamicUniversalTimeOffset(2020, 0);

    double coeff[4] = {9.20, 0.57, 0.10, 0.09}; // Coefficients for nutation equations

    for (int i = 0; i < 4; i++)
    {
        DMStoDecimal(0, 0, coeff[i], coeff[i]);
        cout << coeff[i];
    }

    cout << "\n" << test << endl;
    return 0;
}