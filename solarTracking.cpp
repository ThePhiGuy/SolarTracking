#include "solarTracking.h"



/// @brief Latitude and Longitude explicit-value constructor
/// @param latitude is the geographic latitude you are calculating for
/// @param longitude is the geographic longitude you are calculating for
Sun::Sun(double latitude, double longitude)
{
    earthLatitude = latitude;
    earthLongitude = longitude;

    julianAndGrenwich();
    
    updateValues();
}

/// @brief function that calls other functions to update class internal values
void Sun::updateValues()
{
    // Call all functions needed to update variables in the right order in here.

    // start of calculations internally

    calcApparentLongitude();
    calcElipticObliquity(); // needed before Right Ascension & declination calculations.
    calcRightAscension();
    calcDeclination();
    calcElipticObliquity();
    calcLocalHourAngle();
    calcAltitude();
    calcAzimuth();
    calcSlope();
}

/// @brief Calls all of the needed update-values with the time set manually from an outside user.
/// @param year integer year
/// @param month integer month
/// @param day double fractional day
/// @return string representing the slope of the solar panel at the supplied date/time
string Sun::customTimeUpdate(int year, int month, double day)
{
    JD = Julian::julianDay(year, month, day);
    // JDE = Julian::julianEphimerisDay(year, month, day);
    JDE = JD;
    GMST = Time::greenwichMeanSiderealTime(JD);

    calcApparentLongitude();
    calcElipticObliquity(); // needed before Right Ascension & declination calculations.
    calcRightAscension();
    calcDeclination();
    calcElipticObliquity();
    calcLocalHourAngle();
    calcAltitude();
    calcAzimuth();
    calcSlope();


    double subDay = (day - (int)day);
    double hours = subDay * 24;
    double minutes = (hours - (int)hours) * 60;
    return(to_string(year) + " " + to_string(month) + " " + to_string(day) + "  " + to_string((int)hours) + ":" + to_string(minutes) + "\tSlope : " + to_string(panelSlope) + "\tAltitude : " + to_string(altitude) + " degrees \tAzimuth : " + to_string(azimuth) + "\n");
}

/// @brief function that updates the Julian Date in the class to match that of the current time
void Sun::julianAndGrenwich()
{
    Time::updateUTC(year, month, day);
    JD = Julian::julianDay(year, month, day);
    // JDE = Julian::julianEphimerisDay(year, month, day);
    JDE = JD;
    GMST = Time::greenwichMeanSiderealTime(JD);

    return;
}

/// @brief calculates the apparent longitude based on the Julian Date set within the class
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

/// @brief calculates right ascension utilizing elipctic obliquity and the nutation, apparent latitude and longitude
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

    degreeToRad(localHourAngle);

    return;
}

void Sun::calcAltitude()
{
    double tempLat = earthLatitude;
    degreeToRad(tempLat); // Temporary Latitude used to not interrupt other functions that use latitude in degrees. Fix at some point.

    altitude = asin(sin(tempLat) * sin(declinaton) + cos(tempLat) * cos (declinaton) * cos(localHourAngle));

    return;
}

void Sun::calcAzimuth()
{
    double tempLat = earthLatitude;
    degreeToRad(tempLat); // Temporary Latitude used to not interrupt other functions that use latitude in degrees. Fix at some point.

    azimuth = atan2(sin(localHourAngle), cos(localHourAngle) * sin(tempLat) - tan(declinaton) * cos(tempLat));
    return;
}

void Sun::calcSlope()
{
    // sin panelDec = cos(altitude)cos(azimuth)
    // cos panelHourAngle = sin(altitude) / cos(panelDec) (Equations from Prof. Molnar)
    //
    // These equations convert from the equatorial coordinate system, to one based on the axis of the solar panel
    // this makes it so that the latitude is 0, and we have an "hour angle" and a "declination" (declination represents error in tracking)

    double panelDec = asin(cos(altitude)*cos(azimuth));

    panelSlope = acos(sin(altitude) / cos(panelDec));

    if (azimuth < 0) // if azimuth is greater than 180deg (or flips signs), panel angle should flip.
    {
        panelSlope = panelSlope * -1;
    }

    radToDegree(panelSlope);
    radToDegree(altitude);

    panelSlope += 90; // Sets range of "valid values" on valid solar altitude values to be 0 (facing flat due east) to 180 (facing flat due west)

    return;
}

void Sun::getAltitude()
{
    cout << "\nAltitude of the Sun\t : " << altitude << "degrees\n";
    return;
}

void Sun::getSlope()
{
    for(int i = 0; i < 200; i += 1)
    {
        day += 4/1000.0;
        JD = Julian::julianDay(year, month, day);
        // JDE = Julian::julianEphimerisDay(year, month, day);
        JDE = JD;
        GMST = Time::greenwichMeanSiderealTime(JD);
        updateValues();
        if (altitude > 0)
        {
        cout << "\nDay : " << day << "\tOptimal Solar Panel Slope : " << panelSlope << "\tdegrees\t\t" << altitude << " altitude\n";
        }
    }
    return;
}

void Sun::printDebug() {
    cout << "Lat: " << earthLatitude <<
    "\nLong: " << earthLongitude <<
    "\nApparent Long: " << apparentLongitude <<
    "\nCorrection Omega: " << correctionOmega << // Confirmed close-enough accurate
    "\nEliptical Obliquity: " << elipticObliquity << // Confirmed close-enough accurate.
    "\nObliquity Nutation: " << obliquityNutation << 
    "\nRA: " << rightAscension << // Confirmed Correct
    "\nDec: " << declinaton << // Confirmed Correct
    "\nLocal Hour Angle: " << localHourAngle <<
    "\nAlt: " << altitude <<
    "\nYear: " << year <<
    "\nMonth: " << month <<
    "\nDay: " << day <<
    "\nJulian Date: " << JD <<
    "\nGMST: " << GMST << '\n';
}