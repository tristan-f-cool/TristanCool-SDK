 /*============================================================================
 *  TRISTAN COOL - API
 *  Arduino SDK - DEV
 *  display_tft.cpp
 *============================================================================*/

#include "display_tft.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SETUP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#Constructor - set in <def.h>
Display_TFT::Display_TFT()
{
  // Basic Info
  info.id = "Touchscreen TFT 3.5 320x480";
  info.pin_MOSI = D51_TFT_MOSI;     //pin D51 MOSI
  info.pin_MISO = D50_TFT_MISO;     //pin D50 MISO
  info.pin_DC   = D9_TFT_DC;        //pin D9  DC
  info.pin_CS   = D10_TFT_CS;       //pin D10 CS
  info.pin_CLK  = D52_TFT_CLK;      //pin D52 CLK
  info.pin_XP   = D8_TFT_XP;        //pin D8  X+ Touchscreen
  info.pin_XM   = A3_D57_TFT_XM;    //pin A3  X- Touchscreen
  info.pin_YP   = A2_D56_TFT_YP;    //pin A2  Y+ Touchscreen
  info.pin_YM   = D7_TFT_YM;        //pin D7  Y- Touchscreen
  info.pin_LITE = D11_TFT_LITE;     //pin D11 LITE Backlight
  info.pin_CCS  = D5_SD_CS;         //pin D5  SD Card CS

  // Touch Parameters
  touch.max_x = TOUCH_MAX_X;
  touch.min_x = TOUCH_MIN_X;
  touch.max_y = TOUCH_MAX_Y;
  touch.min_y = TOUCH_MIN_Y;
  touch.max_z = TOUCH_MAX_Z;
  touch.min_z = TOUCH_MIN_Z;
  touch.resistance = TOUCH_RESISTANCE;

  // Backlight
  backlite.screen = LITE_SCREEN;
  backlite.sensor = LITE_SENSOR;
  backlite.manual = LITE_MANUAL;

  // TFT Touchscreen
  tft = new Adafruit_HX8357(info.pin_CS, info.pin_DC);
  touchscreen = new TouchScreen(info.pin_XP, info.pin_YP, info.pin_XM, info.pin_YM, touch.resistance);
}

//#init - called in setup
void Display_TFT::init()
{
  tft->begin();
  tft->setRotation(1);
  tft->fillScreen(HX8357_BLACK);
  tft->fillScreen(HX8357_WHITE);
  flash_screen();
  brightness = 100;
  set_brightness(brightness);
  splashscreen();
  page_id = HOME;
  Serial.print(F("Display TFT: "));
  Serial.print(info.id);
  Serial.println(F(" ... initialized"));
}

//#set pins
void Display_TFT::set_pins(uint8_t MISO, uint8_t MOSI, uint8_t CS, uint8_t DC ,uint8_t CLK, uint8_t XM, uint8_t XP, uint8_t YM, uint8_t YP, uint8_t LITE, uint8_t CCS)
{
  info.pin_MOSI = MOSI;
  info.pin_MISO = MISO;
  info.pin_DC   = DC;
  info.pin_CS   = CS;
  info.pin_CLK  = CLK;
  info.pin_XP   = XP;
  info.pin_XM   = XM;
  info.pin_YP   = YP;
  info.pin_YM   = YM;
  info.pin_LITE = LITE;
  info.pin_CCS  = CCS;
}

//#set touch
void Display_TFT::set_touch(uint8_t xmin, uint8_t xmax, uint8_t ymin, uint8_t ymax, uint8_t zmin, uint8_t zmax, uint8_t resistance)
{
    touch.max_x = xmax;
    touch.min_x = xmin;
    touch.max_y = ymax;
    touch.min_y = ymin;
    touch.max_z = zmax;
    touch.min_z = zmin;
    touch.resistance = resistance;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ OPERATION @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#set brightness mode
void Display_TFT::set_brightness_mode(bool screen_mode, bool sensor_mode, bool manual_mode)
{
  backlite.screen = screen_mode;
  backlite.sensor = sensor_mode;
  backlite.manual = manual_mode;
}

//#set brightness
void Display_TFT::set_brightness(int level)
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
void Display_TFT::flash_screen()
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
void Display_TFT::fade_screen()
{
  for(int i = brightness; i>0; i--)
  {
    set_brightness(i);
    delay(50);
  }
}

//#brighten screen
void Display_TFT::brighten_screen()
{
  for(int i = brightness; i<100; i++)
  {
    set_brightness(i);
    delay(50);
  }
}

//#read touch
TSPoint Display_TFT::read_touch()
{
  touch_point = touchscreen->getPoint();

  //record only if touch is detected
  if(touch_point.x > TOUCH_MIN_Z)
  {
    //swap x and y
    int temp_point = touch_point.x;
    touch_point.x = touch_point.y;
    touch_point.y = temp_point; 
    //Map points to screen (x and y are switched ; y and z are inverted)
    touch_point.x = map(touch_point.x, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, X_MAX);
    touch_point.y = map(touch_point.y, TOUCH_MAX_X, TOUCH_MIN_X, 0, Y_MAX);
    touch_point.z = map(touch_point.z, TOUCH_MAX_Z, TOUCH_MIN_Z, 0, 100);
    //set limits
    if(touch_point.x <0)
    {
      touch_point.x = 0;
    }
    else if(touch_point.x > X_MAX)
    {
      touch_point.x = X_MAX;
    }
    if(touch_point.y <0)
    {
      touch_point.y = 0;
    }
    else if(touch_point.y > Y_MAX)
    {
      touch_point.y = Y_MAX;
    }
  }
  else
  {
    //set points to center and presure to 0
    // touch_point.x = X_CENTRE;
    // touch_point.y = Y_CENTRE;
    touch_point.x = X_MAX;
    touch_point.y = Y_MAX;
    touch_point.z = 0;
  }
   
  return touch_point;
}

//#bitmap image draw //TODO
void Display_TFT::bmpDraw(char *filename, uint8_t x, uint16_t y)
{
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*TFT_BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft->width()) || (y >= tft->height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
//    Serial.print(F("File size: ")); 
    Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
//    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
//    Serial.print(F("Header size: ")); 
    Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
//      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft->width())  w = tft->width()  - x;
        if((y+h-1) >= tft->height()) h = tft->height() - y;
        // Set TFT address window to clipped image bounds
        tft->startWrite(); // Start TFT transaction
        tft->setAddrWindow(x, y, w, h);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            tft->endWrite(); // End TFT transaction
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
            tft->startWrite(); // Start new TFT transaction
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              tft->endWrite(); // End TFT transaction
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
              tft->startWrite(); // Start new TFT transaction
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft->pushColor(tft->color565(r,g,b));
          } // end pixel
        } // end scanline
        tft->endWrite(); // End last TFT transaction
//        Serial.print(F("Loaded in "));
//        Serial.print(millis() - startTime);
//        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
  
}

uint16_t Display_TFT::read16(File &f) 
{
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t Display_TFT::read32(File &f) 
{
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRINT & DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#print info - Serial
void Display_TFT::print_info()
{
  Serial.println(F("_._._._._._._._._._._._._._"));
  Serial.println(F(".----- TFT info   --------."));
  Serial.print(F("Label: "));
  Serial.println(info.id);
  Serial.print(F("pin MOSI: "));
  Serial.println(info.pin_MOSI);
  Serial.print(F("pin MISO: "));
  Serial.println(info.pin_MISO);
  Serial.print(F("pin CS: "));
  Serial.println(info.pin_CS);
  Serial.print(F("pin DC: "));
  Serial.println(info.pin_DC);
  Serial.print(F("pin CLK: "));
  Serial.println(info.pin_CLK);
  Serial.println(F(".----------------."));
  Serial.print(F("pin X+: "));
  Serial.println(info.pin_XP);
  Serial.print(F("pin X-: "));
  Serial.println(info.pin_XM);
  Serial.print(F("pin Y+: "));
  Serial.println(info.pin_YP);
  Serial.print(F("pin Y-: "));
  Serial.println(info.pin_YM);
  Serial.println(F(".----------------."));
  Serial.print(F("pin LITE: "));
  Serial.println(info.pin_LITE);
  Serial.println(F(".----------------."));
  Serial.print(F("pin CCS: "));
  Serial.println(info.pin_CCS);
}

//#print touch - Serial
void Display_TFT::print_touch()
{
  Serial.println(F(".----- TFT touch   --------."));
  Serial.print(F("X/Y: "));
  Serial.print(touch_point.x);
  Serial.print(F(", "));
  Serial.println(touch_point.y);
  Serial.print(F("Pressure %: "));
  Serial.println(touch_point.z);
}

//#print brightness - Serial
void Display_TFT::print_brightness()
{
  Serial.println(F(".----- TFT brightness --------."));
  Serial.print(F("LITE mode(Screen-Sensor-Manual): "));
  Serial.print(backlite.screen);
  Serial.print(F(", "));
  Serial.print(backlite.sensor);
  Serial.print(F(", "));
  Serial.println(backlite.manual);
  Serial.print(F("Brightness %: "));
  Serial.println(brightness);
}

//#print all - Serial
void Display_TFT::print_all()
{
  print_info();
  print_brightness();
  print_touch();
  Serial.println(F("_._._._._._._._._._._._._._"));
}

    
//#display info - screen
void Display_TFT::display_info()
{
  tft->setCursor(20, 20); tft->setTextColor(HX8357_BLUE);  tft->setTextSize(2);
  tft->println(info.id); tft->println();
  tft->drawRect(15, 45, 450, 95, HX8357_YELLOW);

  tft->setTextColor(HX8357_MAGENTA);  tft->print(F("  MISO: "));   tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_MISO); 
  tft->setTextColor(HX8357_GREEN);    tft->print(F("   X+: "));    tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_XP);
  tft->setTextColor(HX8357_CYAN);     tft->print(F("    LITE: ")); tft->setTextColor(HX8357_BLACK);  tft->println(info.pin_LITE); 
  tft->setTextColor(HX8357_MAGENTA);  tft->print(F("  MOSI: "));   tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_MOSI);
  tft->setTextColor(HX8357_GREEN);    tft->print(F("   X-: "));    tft->setTextColor(HX8357_BLACK);  tft->println(info.pin_XM); 
  tft->setTextColor(HX8357_MAGENTA);  tft->print(F("  CS:   "));   tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_CS);
  tft->setTextColor(HX8357_GREEN);    tft->print(F("   Y+: "));    tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_YP);
  tft->setTextColor(HX8357_RED);      tft->print(F("   SD: "));    tft->setTextColor(HX8357_BLACK);  tft->println(info.pin_CCS);
  tft->setTextColor(HX8357_MAGENTA);  tft->print(F("  DC:   "));   tft->setTextColor(HX8357_BLACK);  tft->print(info.pin_DC);
  tft->setTextColor(HX8357_GREEN);    tft->print(F("    Y-: "));   tft->setTextColor(HX8357_BLACK);  tft->println(info.pin_YM);
  tft->setTextColor(HX8357_MAGENTA);  tft->print(F("  CLK:  "));   tft->setTextColor(HX8357_BLACK);  tft->println(info.pin_CLK);
}

//#display touch - screen
void Display_TFT::display_touch()
{
  tft->drawRect(15, 145, 450, 80, HX8357_YELLOW);
  tft->setCursor(20, 172);   tft->setTextSize(3);

  tft->setTextColor(HX8357_GREEN); tft->print(F(" X: ")); tft->setTextColor(HX8357_BLACK); tft->print(touch_point.x);
  tft->setTextColor(HX8357_GREEN); tft->print(F("  Y: ")); tft->setTextColor(HX8357_BLACK); tft->print(touch_point.y);
  tft->setTextColor(HX8357_GREEN); tft->print(F("  Z: ")); tft->setTextColor(HX8357_BLACK); tft->print(touch_point.z);
}

//#display brightness - screen
void Display_TFT::display_brightness()
{
  tft->drawRect(15, 230, 450, 75, HX8357_YELLOW);
  tft->setCursor(25, 260);   tft->setTextSize(3);

  tft->setTextColor(HX8357_CYAN); tft->print(F("Brightness %: ")); tft->setTextColor(HX8357_BLACK); tft->print(brightness);
}

//#display all - screen
void Display_TFT::display_all()
{
  tft->fillScreen(HX8357_WHITE);
  tft->drawRect(10, 10, 460, 300, HX8357_YELLOW);
  display_info();
  display_brightness();
  display_touch();
}

//#display warning - screen
void Display_TFT::display_warning()
{
  tft->setCursor(80, 140);          tft->setTextSize(3);
  tft->setTextColor(HX8357_BLACK);  tft->print("-# WARNING #-"); 
  bmpDraw("warning.bmp",160,72);
  delay(1000);
}

//#display error - screen
void Display_TFT::display_error()
{
  tft->setCursor(80, 140);          tft->setTextSize(3);
  tft->setTextColor(HX8357_BLACK);  tft->print("-# ERROR #-"); 
  bmpDraw("alien.bmp",160,72);
  delay(1000);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ APPLICATION & GRAPHICS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//#splashscreen
void Display_TFT::splashscreen()
{
  bmpDraw("logo.bmp",24,0);
  delay(250);
  bmpDraw("logoinv.bmp",24,0);
  delay(250);
  tft->fillScreen(HX8357_WHITE);
  page_id = HOME;
}

//#screensaver
void Display_TFT::screensaver()
{
  bmpDraw("logo.bmp",24,0);
  delay(250);
  bmpDraw("logoinv.bmp",24,0);
  delay(250);
  page_id = SCREENSAVER;
}

//#main page
void Display_TFT::mainpage()
{
  tft->drawRect(5, 5, 470, 310, HX8357_BLUE);
  bmpDraw("main.bmp",6,6);
}
