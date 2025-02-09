#include <iostream>
#include <iomanip>
#include "julianDate.h"
#include "time.h"
#include "angles.h"

using namespace std;

int main()
{
    double test = dynamicUniversalTimeOffset(2020, 0);

    cout << "\n" << test << endl;
    return 0;
}