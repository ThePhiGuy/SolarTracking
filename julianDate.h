#ifndef julianDate_HPP
#define julianDate_HPP

#include "time.h"

namespace Julian{
double julianDay(int, int, double); // Note - Conversion only good within bounds of 1900-2100
inline double julianToModified(double);

double julianEphimerisDay(int, int, double);
}
#endif