#include <iostream>
#include <iomanip>

#include "angles.h"

using namespace std;

int main()
{

    double test1;

    DMStoDecimal(23,26,21.448, test1);
    cout << "\n" << setprecision(10) << fixed << test1;
    DMStoDecimal(0,0,46.8150, test1);
    cout << "\n" << setprecision(10) << fixed << test1;
    DMStoDecimal(0,0,0.00059, test1);
    cout << "\n" << setprecision(10) << fixed << test1;
    DMStoDecimal(0,0,0.001813, test1);
    cout << "\n" << setprecision(10) << fixed << test1;

    return 0;
}