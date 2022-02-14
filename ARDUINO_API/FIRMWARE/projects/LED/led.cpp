 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - LED
 *  led.cpp
 *============================================================================*/

#include "led.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
LED::LED()
{
  //Basic Info
    info.id = "LED - White";
    info.pin_LED = D13_LED_W;     //pin D13 LED

  //Brightness
    brightness_mode.screen = LITE_SCREEN;
    brightness_mode.sensor = LITE_SENSOR;
    brightness_mode.manual = LITE_MANUAL;

    brightness = 100;
    tc_status = false;
}

//#init
void LED::init()
{
  pinMode(info.pin_LED, OUTPUT);
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
  flash();
}

//#set pins
void LED::set_pins(uint8_t LED)
{
  info.pin_LED = LED;
}

//#set brightness mode
void LED::set_brightness_mode(bool screen_mode, bool sensor_mode, bool manual_mode)
{
  brightness_mode.screen = screen_mode;
  brightness_mode.sensor = sensor_mode;
  brightness_mode.manual = manual_mode;
}

//#LED ON
void LED::on()
{
  digitalWrite(info.pin_LED, HIGH);
  tc_status = true;
  brightness = 100;
}

//#LED OFF
void LED::off()
{
  digitalWrite(info.pin_LED, LOW);
  tc_status = false;
  brightness = 0;
}

//#LED toggle
void LED::toggle()
{
  if(tc_status == true)
  {
      digitalWrite(info.pin_LED, LOW);
      tc_status = false;
      brightness = 0;
  }
  else
  {
      digitalWrite(info.pin_LED, HIGH);
      tc_status = true;
      brightness = 100;    
  }
}

//#LED flash
void LED::flash()
{
  toggle();
  delay(250);
  toggle();
  delay(250);
  toggle();
  delay(250);
  toggle();
  delay(250);
}

//#LED flash - cycles
void LED::flash(int cycles)
{
  for(int i=0; i<cycles*2; i++)
  {
    toggle();
    delay(250);
  }
}

//#LED flash - slow
void LED::flash_slow()
{
  toggle();
  delay(750);
  toggle();
  delay(750);
  toggle();
  delay(750);
  toggle();
  delay(750);
}

//#LED flash - fast
void LED::flash_fast()
{
  toggle();
  delay(100);
  toggle();
  delay(100);
  toggle();
  delay(100);
  toggle();
  delay(100);
}

//#LED set brighten
void LED::set_brightness(int level)
{
  if(level < 0)
  {
    level = 15;
  }
  if(level > 100)
  {
    level = 100;
  }
  level = map(level,0,100,0,255);
  brightness = level;
  analogWrite(info.pin_LED, level);
}

//#LED fade
void LED::fade()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i>0; i--)
  {
    set_brightness(i);
    delay(25);
  }
  tc_status = false;
}

//#LED fade -slow
void LED::fade_slow()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i>0; i--)
  {
    set_brightness(i);
    delay(75);
  }
  tc_status = false;
}

//#LED fade - fast
void LED::fade_fast()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i>0; i--)
  {
    set_brightness(i);
    delay(10);
  }
  tc_status = false;
}

//#LED brighten
void LED::brighten()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i<100; i++)
  {
    set_brightness(i);
    delay(25);
  }
  tc_status = true;
}

//#LED brighten - slow
void LED::brighten_slow()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i<100; i++)
  {
    set_brightness(i);
    delay(75);
  }
  tc_status = true;
}

//#LED brighten - fast
void LED::brighten_fast()
{
  int prev_brightness = brightness;
  for(int i = prev_brightness; i<100; i++)
  {
    set_brightness(i);
    delay(10);
  }
  tc_status = true;
}

//#LED increase brightness
void LED::increase_brightness()
{
  set_brightness(brightness + 10);
}

//#LED decrease brightness
void LED::decrease_brightness()
{
  set_brightness(brightness - 10);
}

//#LED pulse - up
void LED::pulse_up()
{
  for(int i = 475; i > 15; i = i-25)
  {
    on();
    delay(i);
    off();
    delay(i);
  }
}

//#LED pulse - down
void LED::pulse_down()
{
  for(int i = 15; i < 475; i = i+25)
  {
    on();
    delay(i);
    off();
    delay(i);
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void LED::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- LED info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin LED: "));
  Serial.println(info.pin_LED);
}

//#print brightnes - Serial
void LED::print_brightness()
{
  Serial.println(F(".----- LED brightness --------."));
  Serial.print(F("LITE mode(Screen-Sensor-Manual): "));
  Serial.print(brightness_mode.screen);
  Serial.print(F(", "));
  Serial.print(brightness_mode.sensor);
  Serial.print(F(", "));
  Serial.println(brightness_mode.manual);
  Serial.print(F("Brightness %: "));
  Serial.println(brightness);
}

//#print all - Serial
void LED::print_all()
{
  print_info();
  print_brightness();
  Serial.println(F("_._._._._._._._._._._._._._"));
}
