 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - Demux Decoder
 *  demux_decoder.cpp
 *============================================================================*/

#include "demux_decoder.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Demux_Decoder::Demux_Decoder()
{
  info.id = "Demux Decoder";
  info.pin_addr0  = D23_DEMUX_A0;  //pin D23 Demux a0
  info.pin_addr1  = D25_DEMUX_A1;  //pin D25 Demux a1
  info.pin_addr2  = D27_DEMUX_A2;  //pin D27 Demux a2

  byte_value = 0b00000000;
}

String Demux_Decoder::id()
{
  return info.id;
}

String Demux_Decoder::pin()
{
  String pins = String(info.pin_addr0) + ", " + String(info.pin_addr1) + ", " + String(info.pin_addr2);
  return pins;
}

void Demux_Decoder::init()
{
  pinMode(info.pin_addr0, OUTPUT);
  pinMode(info.pin_addr1, OUTPUT);  
  pinMode(info.pin_addr2, OUTPUT);
  Serial.print(info.id);
  byte_value = 0b00000000;
  print_demux();
  Serial.println(F(" ... initialized"));
}

void Demux_Decoder::set_pins(uint8_t a0, uint8_t a1, uint8_t a2)
{
  info.pin_addr0 = a0;
  info.pin_addr1 = a1;
  info.pin_addr2 = a2;
}

void Demux_Decoder::set_output(int output)
{
  if(output < 0)
    output = 0;
  else if(output > 8)
    output = 8;

  switch(output)
  {
    case 0:
      digitalWrite(info.pin_addr0,LOW); 
      digitalWrite(info.pin_addr1,LOW);
      digitalWrite(info.pin_addr2,LOW);
      demux = 0;
      byte_value = 0b00000000;
      break;
    case 1:
      digitalWrite(info.pin_addr0,HIGH); 
      digitalWrite(info.pin_addr1,LOW);
      digitalWrite(info.pin_addr2,LOW);
      demux = 1;
      byte_value = 0b00000001;
      break;
    case 2:
      digitalWrite(info.pin_addr0,LOW); 
      digitalWrite(info.pin_addr1,HIGH);
      digitalWrite(info.pin_addr2,LOW);
      demux = 2;
      byte_value = 0b00000010;
      break;
    case 3:
      digitalWrite(info.pin_addr0,HIGH); 
      digitalWrite(info.pin_addr1,HIGH);
      digitalWrite(info.pin_addr2,LOW);
      demux = 3;
      byte_value = 0b00000100;
      break;
    case 4:
      digitalWrite(info.pin_addr0,LOW); 
      digitalWrite(info.pin_addr1,LOW);
      digitalWrite(info.pin_addr2,HIGH);
      demux = 4;
      byte_value = 0b00001000;
      break;
    case 5:
      digitalWrite(info.pin_addr0,HIGH); 
      digitalWrite(info.pin_addr1,LOW);
      digitalWrite(info.pin_addr2,HIGH);
      demux = 5;
      byte_value = 0b00010000;
      break;
    case 6:
      digitalWrite(info.pin_addr0,LOW); 
      digitalWrite(info.pin_addr1,HIGH);
      digitalWrite(info.pin_addr2,HIGH);
      demux = 6;
      byte_value = 0b00100000;
      break;
    case 7:
      digitalWrite(info.pin_addr0,HIGH); 
      digitalWrite(info.pin_addr1,HIGH);
      digitalWrite(info.pin_addr2,HIGH);
      demux = 7;
      byte_value = 0b01000000;
      break;
    default:
      digitalWrite(info.pin_addr0,LOW); 
      digitalWrite(info.pin_addr1,LOW);
      digitalWrite(info.pin_addr2,LOW);
      demux = 0;
      byte_value = 0b00000000;
      break;
  }
  delay(100);
  
}

void Demux_Decoder::increment()
{
  set_output(demux+1);
}

void Demux_Decoder::decrement()
{
  set_output(demux-1);
}

void Demux_Decoder::outputs_off()
{
  set_output(0);
}

void Demux_Decoder::cascade_up()
{
  for(int i=0; i<8; i++)
    set_output(i);
}

void Demux_Decoder::cascade_down()
{
  for(int i=7; i>0; i--)
    set_output(i);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//


//#Demux Decoder - print info
void Demux_Decoder::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- Demux Decoder info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin a0: "));
  Serial.println(info.pin_addr0);
  Serial.print(F("pin a1: "));
  Serial.println(info.pin_addr1);
  Serial.print(F("pin a2: "));
  Serial.println(info.pin_addr2);
}

//#Demux Decoder - print output value
void Demux_Decoder::print_demux()
{
  Serial.println(demux);
  Serial.println(byte_value,BIN);
}

//#Demux Decoder - print all
void Demux_Decoder::print_all()
{
  print_info();
  print_demux();
}
