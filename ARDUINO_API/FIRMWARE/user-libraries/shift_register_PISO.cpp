 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - Shift Register SIPO
 *  shift_register_PISO.cpp
 *============================================================================*/

#include "shift_register_PISO.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Shift_Register_PISO::Shift_Register_PISO()
{
  info.id = "Shift Register PISO";
  info.pin_load = D32_SR_PISO_load;                   //pin D32 SR PL
  info.pin_datain  = D28_SR_PISO_data;              //pin D28 SR Q7
  info.pin_clockin = D30_SR_PISO_clock;             //pin D30 SR CP

  byte_value = 0b00000000;
}

void Shift_Register_PISO::init()
{
  pinMode(info.pin_load, OUTPUT);
  pinMode(info.pin_clockin, OUTPUT);
  pinMode(info.pin_datain, INPUT);

  Serial.print(info.id);
  byte_value = 0b00000000;
  Serial.println(F(" ... initialized"));
}


String Shift_Register_PISO::id()
{
  return info.id;
}

String Shift_Register_PISO::pin()
{
  String pins = String(info.pin_load) + ", " + String(info.pin_datain) + ", " + String(info.pin_clockin);
  return pins;
}

void Shift_Register_PISO::readShiftRegister()
{
  digitalWrite(info.pin_clockin, HIGH);
  digitalWrite(info.pin_load, HIGH);
  byte_value = shiftIn(info.pin_datain, info.pin_clockin, MSBFIRST);
  delayMicroseconds(5);
  digitalWrite(info.pin_load, LOW);
}

int Shift_Register_PISO::int_value()
{
  return byte_value;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

void Shift_Register_PISO::set_pins(uint8_t load, uint8_t data, uint8_t clk)
{
  info.pin_load = load;
  info.pin_datain  = data;
  info.pin_clockin = clk;
}

void Shift_Register_PISO::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- Shift Register PISO info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin Load: "));
  Serial.println(info.pin_load);
  Serial.print(F("pin Data In: "));
  Serial.println(info.pin_datain);
  Serial.print(F("pin Clock Enable: "));
  Serial.println(info.pin_clockin);
}

void Shift_Register_PISO::print_shift()
{
  Serial.println(byte_value,BIN);
}

void Shift_Register_PISO::print_all()
{
  
}
