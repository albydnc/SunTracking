/*
Sun Tracking Library for Arduino
Based on Sun Equations from the book
Jean Meeus - "Astronomical Algorithms"
Created by Alberto Perro, 2015.
Released into public domain.
*/
#ifndef SunTracking_h
#define SunTracking_h

#include <Arduino.h>
#include <math.h>

class SunTracker
{
public:
  double getRightAscension(int hh,int mm,int ss,int DD, int MM, int YY);
  double getDeclination(int hh,int mm,int ss,int DD, int MM, int YY);
  void setLatLon(double lat, double lon);
  double getAzimuth(int hh,int mm,int ss,int DD, int MM, int YY);
  double getElevation(int hh,int mm,int ss,int DD, int MM, int YY);
private:
  double getAzimuth();
  double getElevation();
  void setJulian(int hh,int mm,int ss,int DD, int MM, int YY);
  void calcSunCoordinates(int hh,int mm,int ss,int DD, int MM, int YY);
  void calcSunCoordinates();
  double _gst, _JD, _JCE, _L0, _M, _e, _Center, _TLon,_TM,_eps,_R,_Omega,_ALon, _RA,_Dec,_HA,_Lat,_Lon;
  constexpr static double DEG2RAD = M_PI/180;
  constexpr static double RAD2DEG = 180/M_PI;
};

#endif
