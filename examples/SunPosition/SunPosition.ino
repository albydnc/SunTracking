/*
Sun Tracking Library for Arduino
Based on Sun Equations from the book
Jean Meeus - "Astronomical Algorithms"
Created by Alberto Perro, 2015.
Released into public domain.
*/
#include <SunTracking.h>
#define LATITUDE  8.0
#define LONGITUDE 40.0
SunTracker Sun;

void setup()
{
  Serial.begin(9600);
  Sun.setLatLon(LATITUDE,LONGITUDE);
}

void loop(){
  float dec = Sun.getDeclination(12,0,0,1,1,2018); //hh:mm:ss DD MM YYYY format (UTC)
  float RA  = Sun.getRightAscension(12,0,0,1,1,2018);
  float Az  = Sun.getAzimuth(12,0,0,1,1,2018);
  float El  = Sun.getElevation(12,0,0,1,1,2018);
  Serial.println("Declination: "+String(dec)+" Right Ascension: "+String(RA));
  Serial.println("Azimuth: "+String(Az)+" Elevation: "+String(El));
  delay(2000);
}
