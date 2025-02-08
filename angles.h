#ifndef ANGLES_HPP
#define ANGLES_HPP

// Collection of functions useful in converting from HMS (hours minutes seconds), Decimal (Decimal Degrees), and DMS (Degrees, Arcminutes, Arcseconds)

inline void HMStoDecimal(int, int, double, double&);
inline void HMStoDMS(int, int, double, int&, int&, double&);
inline void DecimaltoHMS(double, int&, int&, double&);
inline void DecimaltoDMS(double, int&, int&, double&);
inline void DMStoDecimal(int, int, double, double&);
inline void DMStoHMS(int, int, double, int&, int&, double&);

void simplifyDegrees(double&); // Simplifies degree time down into a whole number between 0 and 360

#endif