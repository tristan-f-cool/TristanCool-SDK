 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - LED_RGB
 *  led_rgb.cpp
 *============================================================================*/

#include "led_rgb.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
LED_RGB::LED_RGB()
{
  //Basic Info
    info.id = "LED RGB";
    info.pin_LED_R = D12_LED_R;    //pin D12 LED Red
    info.pin_LED_G = D6_LED_G;     //pin D6  LED Green
    info.pin_LED_B = D4_LED_B;     //pin D4  LED Blue

    red = 0;
    green = 0;
    blue = 0;
    
    tc_status = false;
}

String LED_RGB::id()
{
  return info.id;
}

String LED_RGB::pin()
{
  String pins = String(info.pin_LED_R) + ", " + String(info.pin_LED_G) + ", " + String(info.pin_LED_B);
  return pins;
}

uint32_t LED_RGB::colour()
{
   uint32_t set_colour;
   
    if(red > 192)
    {
      if(green > 192)
      {
        if(blue > 192)
        {
          set_colour = YELLOW;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = YELLOW;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = ORANGE;
        }
        else //(blue < 64)
        {
          set_colour = ORANGE;
        }
      }
      else if ((green < 192) && (green > 128))
      {
        if(blue > 192)
        {
          set_colour = WHITE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = YELLOW;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = YELLOW;
        }
        else //(blue < 64)
        {
          set_colour = ORANGE;
        }
      }
      else if ((green < 128) && (green > 64))
      {
         if(blue > 192)
        {
          set_colour = PURPLE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = PURPLE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = PURPLE;
        }
        else //(blue < 64)
        {
          set_colour = RED;
        } 
      }
      else //(green < 64)
      {
        if(blue > 192)
        {
          set_colour = PURPLE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = PURPLE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = PURPLE;
        }
        else //(blue < 64)
        {
          set_colour = RED;
        }
      }
    }
    
    else if ((red < 192) && (red > 128))
    {
      if(green > 192)
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 192) && (green > 128))
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = WHITE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 128) && (green > 64))
      {
        if(blue > 192)
        {
          set_colour = PURPLE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = WHITE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = WHITE;
        }
        else //(blue < 64)
        {
          set_colour = WHITE;
        } 
      }
      else //(green < 64)
      {
        if(blue > 192)
        {
          set_colour = PURPLE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = PURPLE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = PURPLE;
        }
        else //(blue < 64)
        {
          set_colour = YELLOW;
        }
      }
    }

    else if ((red < 128) && (red > 64))
    {
      if(green > 192)
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 192) && (green > 128))
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 128) && (green > 64))
      {
         if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = WHITE;
        } 
      }
      else //(green < 64)
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = PURPLE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = PURPLE;
        }
        else //(blue < 64)
        {
          set_colour = PURPLE;
        }
      }      
    }
    
    else //(red < 64)
    {
      if(green > 192)
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = GREEN;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 192) && (green > 128))
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        }
      }
      else if ((green < 128) && (green > 64))
      {
         if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE; 
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = GREEN;
        } 
      }
      else //(green < 64)
      {
        if(blue > 192)
        {
          set_colour = BLUE;
        }
        else if ((blue < 192) && (blue > 128))
        {
          set_colour = BLUE;
        }
        else if ((blue < 128) && (blue > 64))
        {
          set_colour = BLUE;
        }
        else //(blue < 64)
        {
          set_colour = PURPLE;
        }
      }
    }

  tc_colour = set_colour;
  tc_colour_txt = colour_txt();
  return tc_colour;
}

String LED_RGB::colour_txt()
{
  switch(tc_colour)
  {
    case WHITE:
      tc_colour_txt = "WHITE";
      break;
    case RED:
      tc_colour_txt = "RED";
      break;
    case ORANGE:
      tc_colour_txt = "ORANGE";
      break;
    case YELLOW:
      tc_colour_txt = "YELLOW";
      break;
    case GREEN:
      tc_colour_txt = "GREEN";
      break;
    case BLUE:
      tc_colour_txt = "BLUE";
      break;
    case PURPLE:
      tc_colour_txt = "PURPLE";
      break;
    case BLACK:
      tc_colour_txt = "OFF";
    case COLOUR:
    default:
      tc_colour_txt = "      ";      
      break;  
  }
 return tc_colour_txt;
}

//#init - setup
void LED_RGB::init()
{
  pinMode(info.pin_LED_R, OUTPUT);
  pinMode(info.pin_LED_G, OUTPUT);
  pinMode(info.pin_LED_B, OUTPUT);
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
  flash();
}

//#set pins
void LED_RGB::set_pins(uint8_t LED_R, uint8_t LED_G, uint8_t LED_B)
{
  info.pin_LED_R = LED_R;
  info.pin_LED_G = LED_G;
  info.pin_LED_B = LED_B;
}

//#RGB ON
void LED_RGB::on()
{
  red = 255;
  green = 255;
  blue = 255;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = WHITE;
  tc_colour_txt = colour_txt();
  
}

//#RGB OFF
void LED_RGB::off()
{
  red = 0;
  green = 0;
  blue = 0;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = false;
  tc_colour = BLACK;
  tc_colour_txt = colour_txt();
}

//#RGB toggle
void LED_RGB::toggle()
{
  if(tc_status == true)
  {
      analogWrite(info.pin_LED_R, 0);
      analogWrite(info.pin_LED_G, 0);
      analogWrite(info.pin_LED_B, 0);
      tc_status = false;
  }
  else
  {
      analogWrite(info.pin_LED_R, red);
      analogWrite(info.pin_LED_G, green);
      analogWrite(info.pin_LED_B, blue);
      tc_status = true;  
  }
}

//#RGB - red
void LED_RGB::go_red()
{
  red = 255;
  green = 0;
  blue = 0;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = RED;
  tc_colour_txt = colour_txt();
}

//#RGB - green
void LED_RGB::go_green()
{
  red = 0;
  green = 255;
  blue = 0;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = GREEN;
  tc_colour_txt = colour_txt();
}

//#RGB - blue
void LED_RGB::go_blue()
{
  red = 0;
  green = 0;
  blue = 255;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = BLUE;
  tc_colour_txt = colour_txt();
}

//#RGB flash - RGB
void LED_RGB::flash()
{
  go_red();
  delay(250);
  go_green();
  delay(250);
  go_blue();
  delay(250);
  off();
}

//#RGB flash - set colour
void LED_RGB::flash(int cycles)
{
  for(int i=0; i<cycles*2; i++)
  {
    toggle();
    delay(250);
  }
}

//#RGB flash - RGB slow
void LED_RGB::flash_slow()
{
  go_red();
  delay(750);
  go_green();
  delay(750);
  go_blue();
  delay(750);
  off();
  delay(100);
}

//#RGB flash - RGB fast
void LED_RGB::flash_fast()
{
  go_red();
  delay(100);
  go_green();
  delay(100);
  go_blue();
  delay(100);
  off();
  delay(100);
}

//#RGB - set colour
void LED_RGB::set_colour(int r, int g, int b)
{
  if(r > 255)
    red = 255;
  else if(r < 0)
    red = 0;
  else
    red = r;

  if(g > 255)
    green = 255;
  else if(g < 0)
    green = 0;
  else
    green = g;

  if(b > 255)
    blue = 255;
  else if(b < 0)
    blue = 0;
  else
    blue = b;
    
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = colour();
  tc_colour_txt = colour_txt();
}

//#RGB - white
void LED_RGB::go_white()
{
  red = 255;
  green = 255;
  blue = 255;
  analogWrite(info.pin_LED_R, red);
  analogWrite(info.pin_LED_G, green);
  analogWrite(info.pin_LED_B, blue);
  tc_status = true;
  tc_colour = WHITE;
  tc_colour_txt = colour_txt();
}

//#RGB - flash white
void LED_RGB::flash_white()
{
  for(int i=0; i<4; i++)
  {
    go_white();
    delay(250);
    off();
    delay(250);
  }
}

//#RGB - flash red
void LED_RGB::flash_red()
{
  for(int i=0; i<4; i++)
  {
    go_red();
    delay(250);
    off();
    delay(250);
  }
}

//#RGB - flash green
void LED_RGB::flash_green()
{
  for(int i=0; i<4; i++)
  {
    go_green();
    delay(250);
    off();
    delay(250);
  }
}

//#RGB - flash blue
void LED_RGB::flash_blue()
{
  for(int i=0; i<4; i++)
  {
    go_blue();
    delay(250);
    off();
    delay(250);
  }
}

//#RGB - rainbow
void LED_RGB::rainbow()
{
  //R-O-Y-G-B-I-V
  //R
  set_colour(255,0,0);
  delay(50);
  //R-O-Y (255,0,0 --> 255,255,0)
  for(int g=0; g <256; g++)
  {
    set_colour(255,g,0);
    delay(5);
  }
  //G (255,255,0 --> 0,255,0)
  for(int r=255; r>0; r--)
  {
    set_colour(r,255,0);
    delay(5);
  }
  //B-I-V (0,255,0 --> 0,255,255)
  for(int b=0; b<256; b++)
  {
    set_colour(0,255,b);
    delay(5);
  }
  //V (0,255,255 --> 0,0,255)
   for(int g=255; g>0; g--)
  {
    set_colour(0,g,255);
    delay(5);
  }
  //V --> R (0,0,255 --> 255,0,255)
  for(int r=0; r<256; r++)
  {
    set_colour(r,0,255);
    delay(5);
  }
  //V --> R (255,0,255 --> 255,0,0)
  for(int b=0; b>0; b--)
  {
    set_colour(255,0,b);
    delay(5);
  }
  delay(50);
}

//#RGB - reverse rainbow
void LED_RGB::reverse_rainbow()
{
  //V-I-B-G-Y-O-R
  //R
  set_colour(255,0,0);
  delay(50);
  //R --> V (255,0,0 --> 255,0,255)
  for(int b=0; b <256; b++)
  {
    set_colour(255,0,b);
    delay(5);
  }
  //V (255,0,255 --> 0,0,255)
  for(int r=255; r>0; r--)
  {
    set_colour(r,0,255);
    delay(5);
  }
  //V-I-B (0,0,255 --> 0,255,255)
  for(int g=0; g<256; g++)
  {
    set_colour(0,g,255);
    delay(5);
  }
  //G (0,255,255 --> 0,255,0)
   for(int b=255; b>0; b--)
  {
    set_colour(0,255,b);
    delay(5);
  }
  //Y-O-R (0,255,0 --> 255,255,0)
  for(int r=0; r<256; r++)
  {
    set_colour(r,255,0);
    delay(5);
  }
  //R (255,255,0 --> 255,0,0)
  for(int g=255; g>0; g--)
  {
    set_colour(255,g,0);
    delay(5);
  }
  delay(50);
}

//#RGB - colour fade
void LED_RGB::fade()
{
  rainbow();
  delay(50);
  reverse_rainbow();
}

//#RGB - colour splash
void LED_RGB::splash()
{
  for(int i = 0; i < 255; i = i+85)
  {
    set_colour(255,0,i);
    delay(200);
    off();
    delay(200);
  }
  for(int i = 255; i > 0; i = i-85)
  {
    set_colour(i,0,255);
    delay(200);
    off();
    delay(200);
  }
  for(int i = 0; i < 255; i = i+85)
  {
    set_colour(0,i,255);
    delay(200);
    off();
    delay(200);
  }
  for(int i = 255; i > 0; i = i-85)
  {
    set_colour(0,255,i);
    delay(200);
    off();
    delay(200);
  }
  for(int i = 0; i < 255; i = i+85)
  {
    set_colour(i,255,0);
    delay(200);
    off();
    delay(200);
  }
  for(int i = 255; i > 0; i = i-85)
  {
    set_colour(255,i,0);
    delay(200);
    off();
    delay(200);
  }
}

//#RGB - siren
void LED_RGB::siren()
{
  go_red();
  delay(100);
  go_white();
  delay(200);
  go_blue();
  delay(100);
}

//#RGB - loading
void LED_RGB::loading()
{
  go_white();
  delay(250);
  go_blue();
  delay(250);
}

//#RGB - error
void LED_RGB::error()
{
  go_white();
  delay(300);
  go_red();
  delay(300);
}

//#RGB - warning
void LED_RGB::warning()
{
  go_white();
  delay(300);
  set_colour(255,255,0);
  delay(300);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#RGB - print info
void LED_RGB::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- LED info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin LED R: "));
  Serial.println(info.pin_LED_R);
  Serial.print(F("pin LED G: "));
  Serial.println(info.pin_LED_G);
  Serial.print(F("pin LED B: "));
  Serial.println(info.pin_LED_B);
}

//#RGB - print colour
void LED_RGB::print_colour()
{
  Serial.println(F(".----- LED RGB colours  --------."));
  Serial.print(F("LED R: "));
  Serial.println(red);
  Serial.print(F("LED G: "));
  Serial.println(green);
  Serial.print(F("LED B: "));
  Serial.println(blue);
}

//#RGB - print all
void LED_RGB::print_all()
{
  print_info();
  print_colour();
  Serial.println(F("_._._._._._._._._._._._._._"));
}
