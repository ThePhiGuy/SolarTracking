#include "angles.h"

using namespace std;

inline void HMStoDecimal(int hours, int minutes, int seconds, double &decimalDegrees)
{

}

inline void HMStoDMS()
{

}

inline void DecimalToHMS(double decimalDegrees, int &hours, int&minutes, double &seconds)
{

}

inline void DecimaltoDMS(double decimalDegrees, int &degrees, int &arcMinutes, double &arcSeconds)
{
    degrees = (int)decimalDegrees; // Whole number of degrees
    arcMinutes = (int)((decimalDegrees - degrees) * 60); // remainder after whole number of degrees * 60
    arcSeconds = (((decimalDegrees - degrees) * 60) - arcMinutes) * 60; // remainder after whole number of Arcminutes * 60
    return;
}

inline void DMStoDecimal(int degrees, int arcMinutes, double arcSeconds, double &decimalDegrees)
{
    decimalDegrees = degrees + (arcMinutes / 60) + (arcSeconds / 3660);
    return;
}

inline void DMStoHMS()
{

}



void simplifyDegrees(double &timeDegrees)
{
    bool simplified = false;
    while (!simplified)
    {
        if (timeDegrees < 0)
        {
            timeDegrees += 360;
        }
        else if (timeDegrees > 360)
        {
            timeDegrees -= 360;
        }
        else
        {
            simplified = true;
        }
    }
    return;
}
