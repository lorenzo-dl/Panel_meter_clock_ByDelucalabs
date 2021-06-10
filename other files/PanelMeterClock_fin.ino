/*
  PanelMeter clock Simple test

  Board: Arduino Pro Mini 5V,should works but is not tested on other arduino boards with te micro atmega 328p.
  Other hardware: DS1307 RTC, 2 50uA current meters with a 100KOhm series resistor.

  It is possible to use for resistor a 82KOhm resistor in series with a 20KOhm resistor for better tuning.

  If you need more documentation about the rtc see the RTClib repository at the link below:
  https://github.com/adafruit/RTClib

  If you neeed more detail about the circuit see the project page at prusaprinters.org:

  Select only pwm enabled pin for the hour and minute pin
 

  Created 08 Jun 2021
  by Lorenzo De Luca

  This example code is in the public domain.

*/
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

// define pins usage

#define HOURPWM 6  //define hour pwm pin
#define MINPWM  5  //define minutes pwm pin


int hourint=0;
int minint=0;


void setup() {
  //Serial for debugging
  Serial.begin(9600);

   if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   while (1);
  }
   if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   // following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }  
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //decomment to set the time
  pinMode(HOURPWM, OUTPUT);     // set hour pwm pin as output
  pinMode(MINPWM, OUTPUT);      // set minute pwm pin as output
}
 



void loop() {
  DateTime now = rtc.now();   //get the time from the rtc

  minint = now.minute();  //put the number of minutes on the variable minint
  hourint = now.hour();   //put the number of hours on the variable minint

  //Serial.print(hourint, DEC);         //decomment this line for debug
  //Serial.print(':');              //decomment this line for debug
  //Serial.println(minint, DEC);    //decomment this line for debug

  if(hourint>12){
    hourint=hourint-12;
  }  
  if(hourint==0) hourint=12;
    
  analogWrite(HOURPWM, map(hourint,1,12,0,255));    //map the howrs range to the dac range (8bit)
  analogWrite(MINPWM, map(minint,0,60,0,255));  //map the minutes range to the dac range (8bit)
  
 delay(200);  //wait until the next reading 

}
