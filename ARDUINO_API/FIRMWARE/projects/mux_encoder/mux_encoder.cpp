 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - Mux Encoder
 *  mux_encoder.cpp
 *============================================================================*/

#include "mux_encoder.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Mux_Encoder::Mux_Encoder()
{
  values = new int[8];
  input_types = new String[8];
}


String Mux_Encoder::id()
{
  return info.id;
}

String Mux_Encoder::pin()
{
  String pins = String(info.pin_addr0) + ", " + String(info.pin_addr1) + ", " + String(info.pin_addr2)+ ", " + String(info.pin_z_com_io);
  return pins;
}

void Mux_Encoder::init()
{
  pinMode(info.pin_addr0, INPUT);
  info.pin_addr0 = HIGH;
  pinMode(info.pin_addr1, INPUT);  
  info.pin_addr1 = HIGH;
  pinMode(info.pin_addr2, INPUT);
  info.pin_addr2 = HIGH;
  pinMode(info.pin_z_com_io, OUTPUT);
  Serial.print(info.id);
  for (int i = 0; i<8; i++)
  {
    values[i]=0;                 //set all values to 0
    input_types[i] = "POT";      //set all inputs as potentiometers
    bitWrite(enable_inputs,i,1); //set all inputs as wired
  }

  print_info();
  Serial.println(F(" ... initialized"));
}

void Mux_Encoder::set_pins(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t z)
{
  info.pin_addr0 = a0;
  info.pin_addr1 = a1;
  info.pin_addr2 = a2;
  info.pin_z_com_io = z;
}

void Mux_Encoder::config_inputs(byte inputs)
{
  enable_inputs = inputs;
}

void Mux_Encoder::config_input_types(String I0, String I1, String I2, String I3, String I4, String I5, String I6, String I7)
{
  input_types[0] = I0;
  input_types[1] = I1;
  input_types[2] = I2;
  input_types[3] = I3;
  input_types[4] = I4;
  input_types[5] = I5;
  input_types[6] = I6;
  input_types[7] = I7;
}

int Mux_Encoder::get_value(int index)
{
  if(index > 7)
    index = 7;
  else if(index < 0)
    index = 0;

  if(bitRead(enable_inputs,index)==1)
  {
    //TODO
    //set_mux()
  }
  else
    return 0;
}

int Mux_Encoder::get_value_percent(int index)
{
  return to_percent(get_value(index));
}

int Mux_Encoder::to_percent(int value)
{
  value = map(value,0,1024,0,100);
  return value;
}

int Mux_Encoder::set_mux(byte input)
{
  //TODO
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

void Mux_Encoder::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(enable_inputs, BIN);
  print_input_types();
  Serial.println(F(".----- Mux Encoder info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin a0: "));
  Serial.println(info.pin_addr0);
  Serial.print(F("pin a1: "));
  Serial.println(info.pin_addr1);
  Serial.print(F("pin a2: "));
  Serial.println(info.pin_addr2);
  Serial.print(F("pin z: "));
  Serial.println(info.pin_z_com_io);

  Serial.println("Y0\tY1\tY2\tY3\tY4\tY5\tY6\tY7");
  Serial.println("---\t---\t---\t---\t---\t---\t---\t---");
}

void Mux_Encoder::print_input_types()
{
  for (int i = 0; i<8; i++)
  {
    if(bitRead(enable_inputs,i)==1)
    {
      Serial.print(input_types[i]); 
    }
    else
      Serial.print(F("NUL"));
    Serial.print("\t");
  }
}

void Mux_Encoder::print_mux()
{
  //TODO
}

void Mux_Encoder::print_values()
{
  //TODO
}

void Mux_Encoder::print_values_percent()
{
  //TODO
}

void Mux_Encoder::print_all()
{
  print_info();
  print_mux();
  print_values();
  print_values_percent();
}
