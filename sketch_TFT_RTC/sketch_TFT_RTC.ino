/*
  TFT and RTC
*/


#include "RTC.h"
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


String getDayOfWeek(DayOfWeek d)
{

  switch(d)
  {
    case DayOfWeek::MONDAY: return "MONDAY";
    case DayOfWeek::TUESDAY: return "TUESDAY";
    case DayOfWeek::WEDNESDAY: return "WEDNESDAY";
    case DayOfWeek::THURSDAY: return "THURSDAY";
    case DayOfWeek::FRIDAY: return "FRIDAY";
    case DayOfWeek::SATURDAY: return "SATURDAY";
    case DayOfWeek::SUNDAY: return "SUNDAY";
  }
  

}



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
  Serial.begin(9600);
  RTC.begin();
  /*
  RTCTime startTime(23, //day
  Month::AUGUST,        // month
  2025,                 // year
  17, 06, 00,          // time
  DayOfWeek::SATURDAY,   // day
  SaveLight::SAVING_TIME_ACTIVE);

  RTC.setTime(startTime);
  */
}

void loop() {

  RTCTime currentTime;
  RTC.getTime(currentTime);
  
  int x = tft.getCursorX();
  int y = tft.getCursorY();

  tft.setCursor(0, 50);
  tft.print(currentTime.getDayOfMonth());
  tft.print("-");
  tft.print(Month2int(currentTime.getMonth()));
  tft.print("-");
  tft.print(currentTime.getYear());

  tft.setCursor(0, 80);
  tft.print(currentTime.getHour());
  tft.print(":");
  tft.print(currentTime.getMinutes());
  tft.print(":");
  tft.print(currentTime.getSeconds());

  Serial.println(x);
  Serial.println(y);
  
  delay(1000); //1sec or 1000ms

}//end program

