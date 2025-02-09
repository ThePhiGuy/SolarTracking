#include "angles.h"

using namespace std;

void HMStoDecimal(int hours, int arcMinutes, double arcSeconds, double &decimalDegrees)
{ // CONFIRMED ACCURATE.
    decimalDegrees = (hours * 15) + ((15 * arcMinutes)/ 60.0) + (15 * arcSeconds / 3600.0); // Decimals added for division to ensure precision of output
    return;  
}

void HMStoDMS(int hours, int arcMinutes, double arcSeconds, int &degrees, int &minutes, double &seconds)
{
    double decimalDegrees;
    HMStoDecimal(hours, arcMinutes, arcSeconds, decimalDegrees);
    DecimaltoDMS(decimalDegrees, degrees, minutes, seconds);
    return;
}

void DecimaltoHMS(double decimalDegrees, int &hours, int&arcMinutes, double &arcSeconds)
{ // CONFIRMED ACCURATE.
    hours = (int)(decimalDegrees/15);
    arcMinutes = (int)(((decimalDegrees / 15) - hours) * 60);
    arcSeconds = ((((decimalDegrees / 15) - hours) * 60) - arcMinutes) * 60;
    return;
}

void DecimaltoDMS(double decimalDegrees, int &degrees, int &minutes, double &seconds)
{
    degrees = (int)decimalDegrees; // Whole number of degrees
    minutes = (int)((decimalDegrees - degrees) * 60); // remainder after whole number of degrees * 60
    seconds = (((decimalDegrees - degrees) * 60) - minutes) * 60; // remainder after whole number of Arcminutes * 60
    return;
}

void DMStoDecimal(int degrees, int minutes, double seconds, double &decimalDegrees)
{
    decimalDegrees = degrees + (minutes / 60.0) + (seconds / 3600.0);
    return;
}

void DMStoHMS(int degrees, int minutes, double seconds, int &hours, int &arcMinutes, double &arcSeconds)
{
    double decimalDegrees;
    DMStoDecimal(degrees, minutes, seconds, decimalDegrees);
    DecimaltoHMS(decimalDegrees, hours, arcMinutes, arcSeconds);
    return;
}



string hmsFormatter(int hours, int arcMinutes, double arcSeconds)
{
    int preDecimal = (int)arcSeconds;
    double postDecimal = arcSeconds - preDecimal;
    
    string formatted = to_string(hours) + "h" + to_string(arcMinutes) + "m" + to_string(preDecimal) + "s." + to_string(postDecimal).erase(0,2);
    return (formatted);
}

string dmsFormatter(int degrees, int minutes, double seconds)
{
    int preDecimal = (int)seconds;
    double postDecimal = seconds - preDecimal;
    
    string formatted = to_string(degrees) + "°" + to_string(minutes) + "'" + to_string(preDecimal) + "\"." + to_string(postDecimal).erase(0,2);
    return (formatted);
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