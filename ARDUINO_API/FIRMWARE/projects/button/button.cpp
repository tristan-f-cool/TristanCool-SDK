 /*============================================================================
 *  TRISTAN COOL - SDK
 *  Arduino API - LED
 *  button.cpp
 *============================================================================*/

#include "button.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
BUTTON::BUTTON()
{
  //Basic Info
    info.id = "BUTTON - Normally Open Momentary";
    info.pin_BUTTON = D2_BUTTON;     //pin D2 BUTTON

    //value = 0;

}

String BUTTON::id()
{
  return info.id;
}

uint8_t BUTTON::pin()
{
  return info.pin_BUTTON;
}


//#init
void BUTTON::init()
{
  pinMode(info.pin_BUTTON, INPUT);
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
  button_state = LOW;
  debounce = 50; //millis
  button_state_change_time = 0;
  state = LOW;
}

//#set pins
void BUTTON::set_pins(uint8_t BUTTON)
{
  info.pin_BUTTON = BUTTON;
}

//#read button pin
byte BUTTON::read_button()
{
  button_state = digitalRead(info.pin_BUTTON);
  return button_state;
}

//#toggle button state
byte BUTTON::read_toggle()
{
  button_state = read_button();
  if(button_state != prev_button_state)
  {
    prev_button_state = button_state;
    if(button_state == LOW)
    {
      state = (state == HIGH) ? LOW: HIGH;
    }
  }
  return state;
}

byte BUTTON::read_toggle_debounce()
{
  if(millis()-button_state_change_time > debounce)
  {
    button_state = read_button();
    if(button_state != prev_button_state)
    {
      button_state_change_time = millis();
      prev_button_state = button_state;
      if(button_state == LOW)
      {
        state = (state == HIGH) ? LOW: HIGH;
      }
    }
  }
  return state;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void BUTTON::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- BUTTON info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin BUTTON: "));
  Serial.println(info.pin_BUTTON);
}

//#print state - Serial
void BUTTON::print_state()
{
  Serial.print(F("BUTTON: "));
  Serial.print(button_state);
}

//#print all - Serial
void BUTTON::print_all()
{
  print_info();
  print_state();
  Serial.println(F("_._._._._._._._._._._._._._"));
}
