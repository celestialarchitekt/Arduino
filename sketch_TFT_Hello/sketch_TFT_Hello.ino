#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>

const int TFT_CS   =  10;
const int TFT_DC   =  9;
const int TFT_RST  =  8;
const int TFT_MOSI =  11;
const int TFT_SCK  =  13;
const int TFT_MISO =  12;

// MOSI is pin 11 and SCK is pin 13 by defaul ,MISO is pin 12

// Hardware SPI: MOSI/SCK from ICSP header
Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  //tft.init(24000000);   // Public init() method, can take SPI freq
  tft.init(8000000); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLUE);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLUE);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("Hello, Mayank!");
  //tft.setCursor(50,60)
  tft.println("Today is a good day!");
}

void loop() {
}
