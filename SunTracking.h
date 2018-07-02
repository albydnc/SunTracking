/*
SunTracking - Library for tracking Sun position
It uses the sun trajectory equations to precisely
calculate the coordinates.

Created by Alberto Perro, September 2014.
Released into the public domain in July 2018.
*/
#ifndef SunTracking_h
#define SunTracking_h

#include <Arduino.h>

class SunTracker
{
public:
  float getRightAscension(int hh,int mm,int ss,int DD, int MM, int YY);
  float getDeclination(int hh,int mm,int ss,int DD, int MM, int YY);
  void setLatLon(float lat, float lon);
  float getAzimuth(int hh,int mm,int ss,int DD, int MM, int YY);
  float getElevation(int hh,int mm,int ss,int DD, int MM, int YY);
private:
  void Julian(int hh,int mm,int ss,int DD, int MM, int YY);
  void SunCoordinates(int hh,int mm,int ss,int DD, int MM, int YY);
  float _JCE, _L0, _M, _e, _Center, _TLon,_TM,_eps,_R,_Omega,_ALon, _RA,_Dec,_HA,_Lat,_Lon;
  float _PI = 3.1415926;
};

#endif
