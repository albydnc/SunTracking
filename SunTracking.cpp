/*
Sun Tracking Library for Arduino
Based on Sun Equations from the book
Jean Meeus - "Astronomical Algorithms"
Created by Alberto Perro, 2015.
Released into public domain.

-- Log:
- 09/23 fixed calculations and major reordering

*/
#include <Arduino.h>
#include <SunTracking.h>

void SunTracker::setJulian(int hh, int mm, int ss, int DD, int MM, int YY)
{
  if (MM <= 2)
  {
    MM += 12;
    YY -= 1;
  }
  double UT = (hh + mm / 60. + ss / 3600.) / 24.;
  int A = floor(YY / 100);
  int B = 2 - A + floor(A / 4);
  _JD = floor(365.25 * (YY + 4716)) + floor(30.6001 * (MM + 1)) + DD + UT + B - 1524.5;
  _JCE = (_JD - 2451545.) / 36525.;
  _gst = 280.46061837 + 360.985647366299*(_JD-2451545) + 0.000387933*_JCE*_JCE- (1./38710000.)*_JCE*_JCE*_JCE;
}
void SunTracker::calcSunCoordinates(int hh, int mm, int ss, int DD, int MM, int YY)
{
  setJulian(hh, mm, ss, DD, MM, YY);
  calcSunCoordinates();
}
void SunTracker::calcSunCoordinates()
{
  double JCE2 = _JCE * _JCE;
  _L0 = (280.46646 + 36000.76893 * _JCE + 0.0003032 * JCE2);
  _L0 = fmod(_L0, 360.);
  _M = 357.52910 + 35999.05030 * _JCE + 0.0001559 * JCE2 - 0.00000048 * JCE2 * _JCE;
  _M = fmod(_M, 360);
  _e = 0.016708617 - 0.000042037 * _JCE - 0.0000001236 * JCE2;
  _Center = (1.914602 - 0.004187 * _JCE - 0.000014 * JCE2) * sin(_M * DEG2RAD) + (0.01993 - 0.000101 * _JCE) * sin(2. * _M * DEG2RAD) + 0.000289 * sin(3. * _M * DEG2RAD);
  _TLon = _L0 + _Center;
  _TM = _M + _Center;
  _R = 1.000001018 * (1 - _e * _e) / (1 + _e * cos(_TM * DEG2RAD));
  _Omega = 125.04 - 1934.136 * _JCE;
  _ALon = _TLon - 0.00569 - 0.00478 * sin(_Omega * DEG2RAD);
  _eps = 23.439291 - 0.01300417 * _JCE - 1.63889e-7 * JCE2 + 5.036111e-7 * JCE2 * _JCE;
  _Dec = RAD2DEG * asin(sin(_eps * DEG2RAD) * sin(_ALon * DEG2RAD));
  _RA = RAD2DEG * atan2(cos(_eps * DEG2RAD) * sin(_ALon * DEG2RAD), cos(_ALon * DEG2RAD));
}

double SunTracker::getDeclination(int hh, int mm, int ss, int DD, int MM, int YY)
{
  calcSunCoordinates(hh, mm, ss, DD, MM, YY);
  return _Dec;
}
double SunTracker::getRightAscension(int hh, int mm, int ss, int DD, int MM, int YY)
{
  calcSunCoordinates(hh, mm, ss, DD, MM, YY);
  return _RA;
}
double SunTracker::getAzimuth(int hh, int mm, int ss, int DD, int MM, int YY)
{
  calcSunCoordinates(hh, mm, ss, DD, MM, YY);
  return getAzimuth();
}
double SunTracker::getElevation(int hh, int mm, int ss, int DD, int MM, int YY)
{
  calcSunCoordinates(hh, mm, ss, DD, MM, YY);
  return getElevation();
}

double SunTracker::getAzimuth()
{
  _HA = _gst + _Lon - _RA;
  double tAz = sin(_HA * DEG2RAD) / (cos(_HA * DEG2RAD) * sin(_Lat * DEG2RAD) - tan(_Dec * DEG2RAD) * cos(_Lat * DEG2RAD));
  return 180 + RAD2DEG * atan(tAz);
}
double SunTracker::getElevation()
{
  _HA = _gst + _Lon - _RA;
  double El = RAD2DEG * asin(sin(_Lat * DEG2RAD) * sin(_Dec * DEG2RAD) + cos(_Lat * DEG2RAD) * cos(_Dec * DEG2RAD) * cos(_HA * DEG2RAD));
  return El;
}

void SunTracker::setLatLon(double lat, double lon)
{
  _Lat = lat;
  _Lon = lon;
}
