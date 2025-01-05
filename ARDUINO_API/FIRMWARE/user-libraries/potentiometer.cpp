 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - LED
 *  pot.cpp
 *============================================================================*/

#include "potentiometer.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
POT::POT()
{
  //Basic Info
    info.id = "POT - 10K ohm";
    info.pin_POT = A0_D54_POT;     //pin A0 POT

    value = 0;

}

String POT::id()
{
  return info.id;
}

uint8_t POT::pin()
{
  return info.pin_POT;
}


//#init
void POT::init()
{
  pinMode(info.pin_POT, INPUT);
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
}

//#set pins
void POT::set_pins(uint8_t POT)
{
  info.pin_POT = POT;
}

int POT::read_value()
{
  value = analogRead(info.pin_POT);
  return value;
}

int POT::read_value_invert()
{
  value = analogRead(info.pin_POT);
  value = map(value,0,1024,1024,0);
  return value;
}

int POT::read_value_polarized()
{
  value = analogRead(info.pin_POT);
  value = map(value,0,1024,-512,512);
  return value;
}

int POT::map_value(int val_min, int val_max)
{
  int x = read_value();
  x = map(value,0,1024,val_min,val_max);
  return x;
}

int POT::to_pwm()
{
  int x = read_value();
  x = map(value,0,1024,0,255);
  return x;
}

int POT::to_percent()
{
  int x = read_value();
  x = map(value,0,1024,0,100);
  return x;
}

int POT::to_degrees()
{
  int x = read_value();
  x = map(value,0,1024,0,360);
  return x;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void POT::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- POT info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin POT: "));
  Serial.println(info.pin_POT);
}

//#print value - Serial
void POT::print_value()
{
  value = read_value();
  int x = value;
  Serial.print(F("VALUE: "));
  Serial.println(value);
  Serial.print(F("INVERT: "));
  Serial.println(x = read_value_invert());
  Serial.print(F("PWM: "));
  Serial.println(x = to_pwm());
  Serial.print(F("PERCENT: "));
  Serial.println(x = to_percent());
  Serial.print(F("DEGREES: "));
  Serial.println(x = to_degrees());
}

//#print all - Serial
void POT::print_all()
{
  print_info();
  print_value();
  Serial.println(F("_._._._._._._._._._._._._._"));
}
