 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - Shift Register SIPO
 *  shift_register_SIPO.cpp
 *============================================================================*/

#include "shift_register_SIPO.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Shift_Register_SIPO::Shift_Register_SIPO()
{
  info.id = "Shift Register SIPO";
  info.pin_latch = D24_SR_SIPO_latch;  //pin D24 SR Latch
  info.pin_data  = D22_SR_SIPO_data;   //pin D22 SR Data
  info.pin_clock = D26_SR_SIPO_clock;  //pin D26 SR Clock

  byte_value = 0b00000000;
}

String Shift_Register_SIPO::id()
{
  return info.id;
}

String Shift_Register_SIPO::pin()
{
  String pins = String(info.pin_latch) + ", " + String(info.pin_data) + ", " + String(info.pin_clock);
  return pins;
}

void Shift_Register_SIPO::init()
{
  pinMode(info.pin_latch, OUTPUT);
  pinMode(info.pin_data, OUTPUT);  
  pinMode(info.pin_clock, OUTPUT);
  Serial.print(info.id);
  byte_value = 0b00000000;
  updateShiftRegister();
  print_shift();
  Serial.println(F(" ... initialized"));
}

void Shift_Register_SIPO::set_pins(uint8_t latch, uint8_t data, uint8_t clk)
{
  info.pin_latch = latch;
  info.pin_data = data;
  info.pin_clock = clk;
}

void Shift_Register_SIPO::updateShiftRegister()
{
   digitalWrite(info.pin_latch, LOW);
   shiftOut(info.pin_data, info.pin_clock, LSBFIRST, byte_value);
   digitalWrite(info.pin_latch, HIGH);
}

void Shift_Register_SIPO::cascade_up_left()
{
  for (int i = 0; i < 8; i++)
  {
    bitSet(byte_value, i);
    updateShiftRegister();
    print_shift();
    delay(500);
  }
}

void Shift_Register_SIPO::cascade_up_right()
{
  set_register(0);
  for (int i = 8; i > 0; i--)
  {
    bitSet(byte_value, i);
    updateShiftRegister();
    print_shift();
    delay(500);
  }
}

void Shift_Register_SIPO::cascade_down_left()
{
  set_register(0b11111111);
  delay(200);
  set_register(0b01111111);
  delay(200);
  set_register(0b00111111);
  delay(200);
  set_register(0b00011111);
  delay(200);
  set_register(0b00001111);
  delay(200);
  set_register(0b00000111);
  delay(200);
  set_register(0b00000011);
  delay(200);
  set_register(0b00000001);
  delay(200);
  set_register(0b00000000);
  delay(200);
}

void Shift_Register_SIPO::cascade_down_right()
{
  set_register(0b11111110);
  delay(200);
  set_register(0b11111100);
  delay(200);
  set_register(0b11111000);
  delay(200);
  set_register(0b11110000);
  delay(200);
  set_register(0b11100000);
  delay(200);
  set_register(0b11000000);
  delay(200);
  set_register(0b10000000);
  delay(200);
  set_register(0b00000000);
  delay(200);
}

void Shift_Register_SIPO::shift_up()
{
  set_register(0);
  delay(200);
  for(int i = 0; i <9; i++)
  {
      bitSet(byte_value, i);
      updateShiftRegister();
      print_shift();
      delay(200);
      bitWrite(byte_value, i,0);
      updateShiftRegister();
      print_shift();
      delay(200);
  }
}

void Shift_Register_SIPO::shift_down()
{
  set_register(0);
  delay(200);
  for(int i = 8; i > 0; i--)
  {
      bitSet(byte_value, i);
      updateShiftRegister();
      print_shift();
      delay(200);
      bitWrite(byte_value, i,0);
      updateShiftRegister();
      print_shift();
      delay(200);
  }
}

void Shift_Register_SIPO::count_up()
{
    for(int i = 0; i < 256; i++)
    {
      set_number(i);
      delay(200);
    }
}

void Shift_Register_SIPO::count_down()
{
    for(int i = 255; i > 0; i--)
    {
      set_number(i);
      delay(200);
    }
}

void Shift_Register_SIPO::count_up_to(int number)
{
  if(number > 255)
    number = 255;

  else if(number <0)
    number = 0;
    
  set_number(0);
  int count = 0;
  
  while(count < number)
  {
    set_number(count);
    delay(1000);
    count++;
  }
  
}

void Shift_Register_SIPO::count_down_from(int number)
{
  if(number > 255)
    number = 255;

  else if(number <0)
    number = 0;

  set_number(number);
  int count = number;

  while(count > 0)
  {
    set_number(count);
    delay(1000);
    count--;
  }
}

void Shift_Register_SIPO::toggle_left()
{
  set_register(0b10101010);
  delay(200);
  for (int i = 0 ; i < 9; i ++)
  {
    set_register(byte_value << 1);
    delay(200);
    bitSet(byte_value, 0);
    updateShiftRegister();
    print_shift();
    delay(200);
    set_register(byte_value << 1);
    delay(200);
  }
}

void Shift_Register_SIPO::toggle_right()
{
  for(int i = 0; i < 9; i++)
  {
    set_register(0b10101010);
    delay(200);
    set_register(~byte_value);
    delay(200);
  }
}

void Shift_Register_SIPO::set_register(byte value)
{
    byte_value = value;
    updateShiftRegister();
    print_shift();

}

void Shift_Register_SIPO::set_number(byte value)
{
    byte_value = value;
    updateShiftRegister();
    print_shift();

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Shift Register SIPO - print info
void Shift_Register_SIPO::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- Shift Register SIPO info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin Latch: "));
  Serial.println(info.pin_latch);
  Serial.print(F("pin Data: "));
  Serial.println(info.pin_data);
  Serial.print(F("pin Clock: "));
  Serial.println(info.pin_clock);
}

//#Shift Register SIPO - print shift value
void Shift_Register_SIPO::print_shift()
{
  Serial.println(byte_value,BIN);
}

//#Shift Register SIPO - print all
void Shift_Register_SIPO::print_all()
{
  
}
