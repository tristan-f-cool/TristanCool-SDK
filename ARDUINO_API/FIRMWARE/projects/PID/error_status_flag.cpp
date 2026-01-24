 /*============================================================================
 *  TRISTAN COOL - API
 *  Arduino SDK - DEV
 *  error_status_flag.cpp
 *============================================================================*/

#include "error_status_flag.h"

//#Constructor - called at declaration
Error_Status_Flag::Error_Status_Flag()
{
  tc_status = NO_ERROR;
  tc_priority = MINOR;
}

//#init - called to set non-defaults
void Error_Status_Flag::init(bool default_status, uint8_t default_priority)
{
  tc_status = default_status;
  tc_priority = default_priority;
}

//#status - return status value
bool Error_Status_Flag::status()
{
  return tc_status;
}

//#priority - return priority value
uint8_t  Error_Status_Flag::priority()
{
  return tc_priority;
}

//#trigger - set status to ERROR
void Error_Status_Flag::trigger()
{
  tc_status = TC_ERROR;
}

//#reset - reset back to NO ERROR
void Error_Status_Flag::reset()
{
  tc_status = NO_ERROR;
}

//#toggle - invert error status value
void Error_Status_Flag::toggle()
{
  if(tc_status == NO_ERROR)
    tc_status = TC_ERROR;
  else if(tc_status == TC_ERROR)
    tc_status = NO_ERROR; 
}

//#set_status - hard set status
void Error_Status_Flag::set_status(bool set_status)
{
  tc_status = set_status;
}

//#set_priority - modify priority
void Error_Status_Flag::set_priority(uint8_t set_priority)
{
  if(set_priority < 0)
    tc_priority = CRITICAL;
  else if(set_priority > 3)
    tc_priority = MINOR;
  else
    tc_priority = set_priority;
}

//#error_print - serial print
void Error_Status_Flag::error_print()
{
  Serial.println(F("!@ ERROR_STATUS_FLAG @!"));
  Serial.print(tc_status);
  Serial.println(tc_priority);
}
