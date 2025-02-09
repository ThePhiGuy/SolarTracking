#include "solarTracking.h"

Sun::Sun()
{
    double latitude = 46.731705;
    double longitude = 116.999939;

    earthLatitude = latitude;
    earthLongitude = longitude;
    
    updateValues();
}

void Sun::updateValues()
{
    julianAndGrenwich();
    // Call all functions needed to update variables in the right order in here.

    // start of calculations internally

    calcApparentLongitude();
    calcElipticObliquity(); // needed before Right Ascension & declination calculations.
    calcRightAscension();
    calcDeclination();
    calcElipticObliquity();
    calcLocalHourAngle();
    calcAltitude();
}

void Sun::julianAndGrenwich()
{
    Time::updateUTC(year, month, day);
    JD = Julian::julianDay(year, month, day);
    JDE = Julian::julianEphimerisDay(year, month, day);
    GMST = Time::greenwichMeanSiderealTime(JD);

    return;
}

void Sun::calcApparentLongitude()
{
    double t1 = ((JDE - 2451545) / 36525.0); // EQ 21.1 Julian Epoch Centuries

    double t2 = t1 * t1; // Calculates T^2 and T^3 once, to use multiple times.
    double t3 = t2 * t1;

    

    double geometricMeanLongitude = 280.46645 + (36000.76983 * t1) + (0.0003032 * t2); // Represented by L0 in Degrees EQ 24.2
    double solarMeanAnomaly = 357.52910 + (35999.05030 * t1) - (0.0001559 * t2)- (0.00000048 * t3); // Represented by M in Degrees Equation 24.3
    degreeToRad(solarMeanAnomaly); // converted for next equation use

    double solarEquationOfCenter = (1.914600 - (0.004817 * t1) - (0.000014 * t2)) * sin(solarMeanAnomaly)
                                    + (0.019993 - 0.000101 * t1) * sin(2*solarMeanAnomaly)
                                    + 0.000290 * sin(3*solarMeanAnomaly); // represented by C in degrees EQ 24.4.1?

    double trueLongitude = geometricMeanLongitude + solarEquationOfCenter;


    correctionOmega = 125.04 - (1934.136 * t1); // output in degrees
    degreeToRad(correctionOmega); // converts to radians for calculation

    apparentLongitude = trueLongitude - 0.00569 - (0.00478 * sin(correctionOmega)); // output in degrees represented by lambda

    degreeToRad(apparentLongitude); // switches output to be in radians for RA and DEC calculations

    return;
}

void Sun::calcRightAscension()
{
    double correctionAmount = 0.00256 * cos(correctionOmega); // Correction Mentioned for obliquity
    degreeToRad(correctionAmount);

    double correctedEclipticObliquity = elipticObliquity + correctionAmount; // obliquity input into function in radians

    rightAscension = atan2(cos(correctedEclipticObliquity) * sin(apparentLongitude), cos(apparentLongitude));

    radToDegree(rightAscension);

    return;
}

void Sun::calcDeclination()
{
    double correctionAmount = 0.00256 * cos(correctionOmega); // Correction mentioned for obliquity
    degreeToRad(correctionAmount);

    double correctedEclipticObliquity = elipticObliquity + correctionAmount; // obliquity input into function in radians

    declinaton = asin(sin(correctedEclipticObliquity) * sin(apparentLongitude));

    return;
}


void Sun::calcElipticObliquity()
{
    calcObliquityNutation();

    double t1 = ((JDE - 2451545) / 36525.0); // EQ 21.1 Julian Epoch Centuries

    double t2 = t1 * t1;
    double t3 = t2 * t1;

    double meanObliquity = 23.439291111  - (0.0130041667 * t1) - (0.0000001639 * t2) + (0.0000005036 * t3); // meanObliquity in terms of Decimal Degrees

    elipticObliquity = meanObliquity - obliquityNutation; // true obliquity in decimal degrees

    degreeToRad(elipticObliquity); // Outputs in rads for other functions trig
    return;
}


void Sun::calcObliquityNutation()
{
    double t1 = ((JDE - 2451545) / 36525.0); // EQ 21.1 Julian Epoch Centuries

    double t2 = t1 * t1; // Calculates T^2 and T^3 once, to use multiple times.
    double t3 = t2 * t1;

    double solarMeanLongitude = 280.46645 + (36000.76983 * t1) + (0.0003032 * t2); // Represented by L in Degrees EQ 24.2
    double lunarMeanLongitude = 218.3165 + (481267.8813 * t1); // Represented by L' in Degrees

    double lunarOmega = 125.04452 - (1934.136261 * t1) + (0.0020708 * t2) + (t3 / 450000); // Represented by omega in Degrees
    
    degreeToRad(solarMeanLongitude); // Converts both values to Radians for trig calculations
    degreeToRad(lunarMeanLongitude);
    degreeToRad(lunarOmega);


    obliquityNutation = (0.002555555 * cos(lunarOmega)) + (0.00015833 * cos(2 * solarMeanLongitude)) + (0.0000277777778 * cos (2 * lunarMeanLongitude)) - (0.00002500001 * cos(2 * lunarOmega));
    // EQ on page 132 above Table 21A (I think this is right, converted all of the values from arcseconds to decimal degrees)
    // Output in Degrees
    return;
}

void Sun::calcLocalHourAngle()
{
    localHourAngle = GMST - earthLongitude - rightAscension; // All values in degrees, output LHA is in Degrees.

    simplifyDegrees(localHourAngle);

    degreeToRad(localHourAngle);

    return;
}

void Sun::calcAltitude()
{
    double tempLat = earthLatitude;
    degreeToRad(tempLat); // Temporary Latitude used to not interrupt other functions that use latitude in degrees. Fix at some point.

    degreeToRad(localHourAngle); 

    altitude = asin(sin(tempLat) * sin(declinaton) + cos(tempLat) * cos (declinaton) * cos(localHourAngle));

    radToDegree(altitude);
    return;
}

void Sun::getAltitude()
{
    cout << "\nI Hope this works\t" << altitude << '\n';
    return;
}

void Sun::printDebug() {
    cout << "Lat: " << earthLatitude <<
    "\nLong: " << earthLongitude <<
    "\nApparent Long: " << apparentLongitude <<
    "\nCorrection Omega: " << correctionOmega <<
    "\nEliptical Obliquity: " << elipticObliquity <<
    "\nObliquity Nutation: " << obliquityNutation <<
    "\nRA: " << rightAscension <<
    "\nDec: " << declinaton <<
    "\nLocal Hour Angle: " << localHourAngle <<
    "\nAlt: " << altitude <<
    "\nYear: " << year <<
    "\nMonth: " << month <<
    "\nDay: " << day <<
    "\nJulian Date: " << JD <<
    "\nJulian Date Ephimeris: " << JDE <<
    "\nGMST: " << GMST << '\n';
}