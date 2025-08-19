#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

// MOSI is pin 11 and SCK is pin 13 by default, ,MISO is pin 12

// Hardware SPI: MOSI/SCK from ICSP header
Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.init(24000000);   // Public init() method, can take SPI freq
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(40, 60);
  tft.print("Hello, Mayank!");
}

void loop() {
}
