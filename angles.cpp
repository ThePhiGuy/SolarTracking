#include "angles.h"

using namespace std;

inline void HMStoDecimal(int hours, int arcMinutes, int arcSeconds, double &decimalDegrees)
{
    hours = (int)(decimalDegrees/15);
    arcMinutes = 
}

inline void HMStoDMS(int hours, int arcMinutes, double arcSeconds, int &degrees, int &minutes, double &seconds)
{

}

inline void DecimalToHMS(double decimalDegrees, int &hours, int&minutes, double &seconds)
{

}

inline void DecimaltoDMS(double decimalDegrees, int &degrees, int &minutes, double &seconds)
{
    degrees = (int)decimalDegrees; // Whole number of degrees
    minutes = (int)((decimalDegrees - degrees) * 60); // remainder after whole number of degrees * 60
    seconds = (((decimalDegrees - degrees) * 60) - minutes) * 60; // remainder after whole number of Arcminutes * 60
    return;
}

inline void DMStoDecimal(int degrees, int minutes, double seconds, double &decimalDegrees)
{
    decimalDegrees = degrees + (minutes / 60) + (seconds / 3660);
    return;
}

inline void DMStoHMS(int degrees, int minutes, int seconds, int &hours, int &arcMinutes, int &arcSeconds)
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
