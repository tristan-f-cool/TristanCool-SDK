 /*============================================================================
 *  TRISTAN COOL - API
 *  Arduino SDK - DEV
 *  display_lcd.cpp
 *============================================================================*/

#include "display_lcd.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Display_LCD::Display_LCD()
{
  // Basic Info
  info.id = "LCD 16x2 - white on blue";

  // Pins
  info.pin_RS     = D50_LCD_RS;
  info.pin_ENABLE = D51_LCD_ENABLE;
  info.pin_DB4    = D7_LCD_DB4;
  info.pin_DB5    = D8_LCD_DB5;
  info.pin_DB6    = D9_LCD_DB6;
  info.pin_DB7    = D10_LCD_DB7;
  info.pin_LITE   = D11_LCD_LITE;
  

  // Backlight
  backlite.sensor = LITE_SENSOR;
  backlite.manual = LITE_MANUAL;

  // LCD
  lcd = new LiquidCrystal(D50_LCD_RS,D51_LCD_ENABLE,D7_LCD_DB4,D8_LCD_DB5,D9_LCD_DB6,D10_LCD_DB7);
  info.COLUMN = LCD_COLUMN;
  info.ROW = LCD_ROW;

  lcd->createChar(0,custom.T);
  lcd->createChar(1,custom.C);
  lcd->createChar(2,custom.logo);
}

//#init - called in setup
void Display_LCD::init()
{
  lcd->begin(info.COLUMN,info.ROW);
  
  flash_screen();
  brightness = 100;
  set_brightness(brightness);
  splashscreen();
  page_id = HOME;
  Serial.print(F("Display LCD: "));
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
  display_all();
}

//#set pins
void Display_LCD::set_pins(uint8_t RS, uint8_t ENABLE, uint8_t DB4, uint8_t DB5, uint8_t DB6, uint8_t DB7, uint8_t LITE)
{
  info.pin_RS     = RS;
  info.pin_ENABLE = ENABLE;
  info.pin_DB4    = DB4;
  info.pin_DB5    = DB5;
  info.pin_DB6    = DB6;
  info.pin_DB7    = DB7;
  info.pin_LITE   = LITE;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ OPERATION @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#set brightness mode
void Display_LCD::set_brightness_mode(bool sensor_mode, bool manual_mode)
{
  backlite.sensor = sensor_mode;
  backlite.manual = manual_mode;
}

//#set brightness
void Display_LCD::set_brightness(int level)
{
  if(level < 0)
    level = 10;
  else if(level > 100)
    level = 100;
 
  brightness = level;
  level = map(level,0,100,0,255);
  analogWrite(info.pin_LITE, level);
}

//#flash screen
void Display_LCD::flash_screen()
{
  set_brightness(25);
  delay(500);
  set_brightness(100);
  delay(500);
  set_brightness(25);
  delay(500);
  set_brightness(100);
  delay(500);
}

//#fade screen
void Display_LCD::fade_screen()
{
  for(int i = brightness; i>0; i--)
  {
    set_brightness(i);
    delay(50);
  }
}

//#brighten screen
void Display_LCD::brighten_screen()
{
  for(int i = brightness; i<100; i++)
  {
    set_brightness(i);
    delay(50);
  }
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void Display_LCD::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- LCD info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("Columns: "));
  Serial.println(info.COLUMN);
  Serial.print(F("Rows: "));
  Serial.println(info.ROW);
  Serial.print(F("pin RS: "));
  Serial.println(info.pin_RS);
  Serial.print(F("pin ENABLE: "));
  Serial.println(info.pin_ENABLE);
  Serial.print(F("pin DB4: "));
  Serial.println(info.pin_DB4);
  Serial.print(F("pin DB5: "));
  Serial.println(info.pin_DB5);
  Serial.print(F("pin DB6: "));
  Serial.println(info.pin_DB6);
  Serial.print(F("pin DB7: "));
  Serial.println(info.pin_DB7);
  Serial.println(info.pin_LITE);
  Serial.println(F(".----------------."));
  Serial.print(F("pin LITE: "));
  Serial.println(info.pin_LITE);
  Serial.println(F(".----------------."));
}

//#print brightness - Serial
void Display_LCD::print_brightness()
{
  Serial.println(F(".----- LCD brightness --------."));
  Serial.print(F("LITE mode(Sensor-Manual): "));
  Serial.print(backlite.sensor);
  Serial.print(F(", "));
  Serial.println(backlite.manual);
  Serial.print(F("Brightness %: "));
  Serial.println(brightness);
}

//#print all - Serial
void Display_LCD::print_all()
{
  print_info();
  print_brightness();
  Serial.println(F("_._._._._._._._._._._._._._"));
}

//#no display - hide screen
void Display_LCD::no_display()
{
  lcd->noDisplay();
}

//#show display - show screen
void Display_LCD::show_display()
{
  lcd->display();
}

//#blink cursor - blink underline cursor
void Display_LCD::blink_cursor()
{
  lcd->cursor();
  delay(200);
  lcd->noCursor();
  delay(200);
  lcd->cursor();
  delay(200);
  lcd->noCursor();
  delay(200);
}

//#blink cell - blink cell at cursor
void Display_LCD::blink_cell()
{
  lcd->blink();
  delay(200);
  lcd->noBlink();
  delay(200);
  lcd->blink();
  delay(200);
  lcd->noBlink();
  delay(200);
}

//#display info - screen
void Display_LCD::display_info()
{
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Info: ");

  lcd->setCursor(5, 0);
  lcd->print("RS:");
  lcd->print(info.pin_RS); 
  lcd->print(" EN:");
  lcd->print(info.pin_ENABLE); 

  lcd->setCursor(9, 1);
  lcd->print("LITE:");
  lcd->print(info.pin_LITE); 
  
  delay(2000);

  lcd->setCursor(0, 0);
  for(int i = 0; i <16; i++)
  {
    lcd->scrollDisplayRight();
    delay(50);
  }

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("DB4:");
  lcd->print(info.pin_DB4); 
  lcd->print(" DB5:");
  lcd->print(info.pin_DB5); 
  
  lcd->setCursor(0, 1);
  lcd->print("DB6:");
  lcd->print(info.pin_DB6); 
  lcd->print(" DB7:");
  lcd->print(info.pin_DB7); 
  
  delay(2000);

 
  lcd->setCursor(0, 0);
  for(int i = 0; i <16; i++)
  {
    lcd->scrollDisplayRight();
    delay(50);
  }

  delay(500);
  lcd->clear();
}


//#display brightness - screen
void Display_LCD::display_brightness()
{
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Brightness: %");
  lcd->setCursor(0, 1);
  lcd->print(brightness);
  
  delay(2000);
  lcd->clear();
}

//#display all - screen
void Display_LCD::display_all()
{
  display_info();
  delay(500);
  display_brightness();
  delay(500);
  lcd->clear();
}

//#display warning - screen
void Display_LCD::display_warning()
{
  lcd->clear();
  lcd->setCursor(2, 0);
  lcd->print("& WARNING &");
  lcd->setCursor(0, 1);
}

//#display error - screen
void Display_LCD::display_error()
{
  lcd->clear();
  lcd->setCursor(3, 0);
  lcd->print("% ERROR %");
  lcd->setCursor(0, 1);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ APPLICATION & GRAPHICS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#splashscreen
void Display_LCD::splashscreen()
{
    blink_cell();
 
    lcd->setCursor(0, 0);
    lcd->write(byte(0));
    delay(150);
    lcd->setCursor(1, 0);
    lcd->write(byte(1));
    delay(150);
    lcd->setCursor(2, 0);
    lcd->write(byte(2));
    delay(1200);
    
    blink_cursor();

    String title = "Tristan-Cool SDK";
    lcd->setCursor(0, 1);
    lcd->print(title);
    
    lcd->setCursor(16, 0);
    lcd->print("*Arduino API*");
    delay(1800);
    
    for(int i = 0; i <16; i++)
    {
      lcd->scrollDisplayLeft();
      delay(300);
    }

    delay(750);
    lcd->clear();

}

//#screensaver
void Display_LCD::screensaver()
{
  no_display();
  fade_screen();
  delay(800);
  brighten_screen();

  show_display();

  char title[6] = {'T','C','~','L','C','D'};
  
  lcd->setCursor(11,0);
  lcd->autoscroll();
  for(int i = 0; i<sizeof(title) ;i++)
  {
    lcd->print(title[i]);
    delay(220);
  }
  
  lcd->setCursor(11,1);
  lcd->noAutoscroll();
  for(int i = 0; i<sizeof(title) ;i++)
  {
    lcd->print(title[i]);
    delay(220);
  }

  lcd->clear();
  lcd->setCursor(7,0);
  for(int i = 0; i<sizeof(title) ;i++)
  {
    lcd->setCursor(8,0);
    lcd->print(title[i]);
    delay(440);
  }
  
  delay(100);
  lcd->clear();
}

//#main page
void Display_LCD::mainpage()
{
  blink_cell();
  blink_cursor();
  lcd->setCursor(0,0);
  lcd->print("!TODO!");
}
