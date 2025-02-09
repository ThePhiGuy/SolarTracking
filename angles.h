#ifndef ANGLES_HPP
#define ANGLES_HPP

#include <string>
using namespace std;

// Collection of functions useful in converting from HMS (hours, arcminutes, arcseconds), Decimal (Decimal Degrees), and DMS (Degrees, minutes, seconds)

void HMStoDecimal(int, int, double, double&);
void HMStoDMS(int, int, double, int&, int&, double&);
void DecimaltoHMS(double, int&, int&, double&);
void DecimaltoDMS(double, int&, int&, double&);
void DMStoDecimal(int, int, double, double&);
void DMStoHMS(int, int, double, int&, int&, double&);

string hmsFormatter(int, int, double);
string dmsFormatter(int, int, double);

void simplifyDegrees(double&); // Simplifies degree time down into a whole number between 0 and 360

#endif