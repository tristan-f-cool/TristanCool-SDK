 /*============================================================================
 *  TRISTAN COOL - API
 *  Arduino SDK - DEV
 *  display_oled.cpp
 *============================================================================*/

#include "display_oled.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Display_OLED::Display_OLED()
{
  // Basic Info
  info.id = "OLED SSD1306 0.96 128x64";
  info.pin_MOSI   = D51_OLED_MOSI;     //pin D51 MOSI
  info.pin_CLK    = D52_OLED_CLK;      //pin D52 CLK
  info.pin_DC     = D9_OLED_DC;        //pin D9  DC
  info.pin_RESET  = D11_OLED_RESET;    //pin D11 RESET
  info.pin_CS     = D10_OLED_CS;       //pin D10 CS

  // OLED screen
  oled = new Adafruit_SSD1306 (OLED_WIDTH, OLED_HEIGHT, info.pin_MOSI, info.pin_CLK, info.pin_DC, info.pin_RESET, info.pin_CS);
}

//#init - called in setup
void Display_OLED::init()
{
  oled->clearDisplay();
  //splashscreen();
  page_id = HOME;
  Serial.print(F("Display OLED: "));
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
}

//#set pins
void Display_OLED::set_pins(uint8_t MOSI, uint8_t CLK, uint8_t DC, uint8_t RESET, uint8_t CS)
{
  info.pin_MOSI   = MOSI;
  info.pin_CLK    = CLK;
  info.pin_DC     = DC;
  info.pin_RESET  = RESET;
  info.pin_CS     = CS;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ OPERATION @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void Display_OLED::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- OLED info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin MOSI: "));
  Serial.println(info.pin_MOSI);
  Serial.print(F("pin CLK: "));
  Serial.println(info.pin_CLK);
  Serial.print(F("pin DC: "));
  Serial.println(info.pin_DC);
  Serial.print(F("pin RESET: "));
  Serial.println(info.pin_RESET);
  Serial.print(F("pin CS: "));
  Serial.println(info.pin_CS);
  Serial.println(F(".----------------."));
}

//#print all - Serial
void Display_OLED::print_all()
{
  print_info();
  Serial.println(F("_._._._._._._._._._._._._._"));
}

    
//#display info - screen
void Display_OLED::display_info()
{
  oled->clearDisplay();
  oled->fillRect(0, 0, 48, 64, SSD1306_WHITE);
  oled->drawRect(48,0, 80, 64, SSD1306_WHITE);
  oled->drawLine(0, 13, 48, 13, SSD1306_BLACK);
  oled->drawLine(0, 26, 48, 26, SSD1306_BLACK);
  oled->drawLine(0, 39, 48, 39, SSD1306_BLACK);
  oled->drawLine(0, 52, 48, 52, SSD1306_BLACK);
  oled->drawLine(48, 13, 126, 13, SSD1306_WHITE);
  oled->drawLine(48, 26, 126, 26, SSD1306_WHITE);
  oled->drawLine(48, 39, 126, 39, SSD1306_WHITE);
  oled->drawLine(48, 52, 126, 52, SSD1306_WHITE);
  oled->setTextSize(1);
  oled->setTextColor(SSD1306_BLACK);
  oled->setCursor(4, 4);
  oled->println(F("MOSI"));
  oled->setCursor(4, 16);
  oled->println(F("CLK"));
  oled->setCursor(4, 29);
  oled->println(F("DC"));
  oled->setCursor(4, 43);
  oled->println(F("RESET"));
  oled->setCursor(4, 55);
  oled->println(F("C/S"));
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(52, 4);
  oled->println(info.pin_MOSI);
  oled->setCursor(52, 16);
  oled->println(info.pin_CLK);
  oled->setCursor(52, 29);
  oled->println(info.pin_DC);
  oled->setCursor(52, 43);
  oled->println(info.pin_RESET);
  oled->setCursor(52, 55);
  oled->println(info.pin_CS);
  oled->display();
  delay(2000);
}

//#display all - screen
void Display_OLED::display_all()
{
  display_info();
}

//#display warning - screen
void Display_OLED::display_warning()
{
  oled->clearDisplay();
  oled->drawRoundRect(0, 6, 124, 40, 8, SSD1306_WHITE);
  oled->fillTriangle(16, 12, 4, 36, 24, 36, SSD1306_WHITE);
  oled->setTextSize(2);
  oled->setTextColor(SSD1306_BLACK);
  oled->setCursor(10, 20);
  oled->println(F("!"));
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(30, 18);
  oled->println(F("WARNING"));
  oled->setCursor(34, 50);
  oled->println(F("####"));
  oled->display();
  delay(2000);
}

//#display error - screen
void Display_OLED::display_error()
{
  oled->clearDisplay();
  oled->fillRect(0,0, oled->width()-1, oled->height()-1, SSD1306_WHITE);
  oled->fillRoundRect(2, 6, 122, 40, 8, SSD1306_BLACK);
  oled->drawCircle(20, 24, 12, SSD1306_WHITE);
  oled->setTextSize(2);
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(16, 18);
  oled->println(F("X"));
  oled->setCursor(42, 18);
  oled->println(F("ERROR"));
  oled->setTextColor(SSD1306_BLACK);
  oled->setCursor(36, 48);
  oled->println(F("####"));
  oled->display();
  delay(2000);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ APPLICATION & GRAPHICS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#splashscreen
void Display_OLED::splashscreen()
{
  oled->clearDisplay();
  oled->drawBitmap(0, 0, logo_inv, 128, 64, SSD1306_WHITE);
  oled->display();
  delay(3000);
  oled->clearDisplay();
  oled->drawBitmap(0, 0, logo, 128, 64, SSD1306_WHITE);
  oled->display();
  delay(3000);
  
  oled->clearDisplay();
  oled->drawRect(0, 0, oled->width()-1, oled->height()-1, SSD1306_WHITE);
  oled->fillRect(0, (oled->height()*2/3), oled->width()-1, (oled->height()/3)-1, SSD1306_WHITE);
  oled->setTextSize(1);
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(4, 4);
  oled->println(F("Tristan Cool SDK"));
  oled->setTextSize(2);
  oled->setTextColor(SSD1306_BLACK);
  oled->setCursor(4, 44);
  oled->println(F("ArduinoAPI"));
  oled->setTextSize(2);
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(4, 20);
  oled->println(F("OLED"));
  oled->display();     
  delay(2000);

  // Scroll in various directions, pausing in-between:
  oled->drawRect(0, 16, oled->width()-1, 24, SSD1306_BLACK);
  oled->display(); 
  oled->startscrollright(0x02, 0x04);
  delay(5000);
  oled->stopscroll();
  delay(1000);
  oled->startscrollleft(0x02, 0x04);
  delay(5000);
  oled->stopscroll();
  delay(500);
  page_id = HOME;
}

//#screensaver

#define XPOS   0 
#define YPOS   1
#define DELTAY 2
#define NUMSTARS 6
#define LOGO_W 32
#define LOGO_H 32

void Display_OLED::screensaver()
{
  int8_t f, icons[NUMSTARS][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMSTARS; f++) 
  {
    icons[f][XPOS]   = random(1 - LOGO_W, oled->width());
    icons[f][YPOS]   = -LOGO_H;
    icons[f][DELTAY] = random(1, NUMSTARS);
  }

  for(;;) //TODO - replace with condition
  { // Loop forever...
    oled->clearDisplay(); // Clear the display buffer

    // Draw each star
    for(f=0; f< NUMSTARS; f++) 
    {
      oled->drawBitmap(icons[f][XPOS], icons[f][YPOS], star, LOGO_W, LOGO_H, SSD1306_WHITE);
    }

    oled->display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each star...
    for(f=0; f< NUMSTARS; f++) 
    {
      icons[f][YPOS] += icons[f][DELTAY];
      // If star is off the bottom of the screen...
      if (icons[f][YPOS] >= oled->height()) 
      {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_W, oled->width());
        icons[f][YPOS]   = -LOGO_H;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
  page_id = SCREENSAVER;
}

//#main page
void Display_OLED::mainpage()
{
  oled->clearDisplay();
  oled->drawRect(0, 0, oled->width()-1, oled->height()-1, SSD1306_WHITE);
  oled->display();
  delay(2000);
  page_id = HOME;
}
