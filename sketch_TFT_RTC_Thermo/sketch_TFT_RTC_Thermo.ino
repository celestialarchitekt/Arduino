/*
  TFT and RTC
*/


#include "RTC.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>
#include <Modulino.h>
#include <vector>


ModulinoThermo thermo;


const int TFT_CS   =  10;
const int TFT_DC   =  9;
const int TFT_RST  =  8;
const int TFT_MOSI =  11;
const int TFT_SCK  =  13;
const int TFT_MISO =  12;

int seconds=0;

// MOSI is pin 11 and SCK is pin 13 by defaul ,MISO is pin 12

// Hardware SPI: MOSI/SCK from ICSP header
Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);

/* just for reference
enum class DayOfWeek {
  MONDAY = 0,   // case 0
  TUESDAY,      // 1
  WEDNESDAY,    // 2
  THURSDAY,     // 3
  FRIDAY,       // 4
  SATURDAY,     // 5
  SUNDAY        // 6
};
*/


/*
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
*/


String getDayOfWeek(DayOfWeek d)
{
  static std::vector<String> days = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};  
  return days[int(d)-1];
}




void setup() {
  
  Serial.begin(9600);
  RTC.begin();

  tft.init(8000000); 

  tft.setRotation(1);
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("Hello, Mayank!");
  tft.println("You are the guide.");
  
  
  while (!Serial); // wait till the Serial monitor is ready

  // setup the modulino
  Modulino.begin();
  if (!thermo.begin()) {
    Serial.println("Thermo module not responding");
    while (1); // doesnt let it go to void loop() if INIT fails
  }

  
  // RTC first time setup
  
  
  RTCTime startTime(2, //day
  Month::OCTOBER,        // month
  2025,                 // year
  10, 45 , 00,          // time
  DayOfWeek::THURSDAY,   // day
  SaveLight::SAVING_TIME_ACTIVE);
  RTC.setTime(startTime);
  

}

void loop() {

  RTCTime currentTime;
  RTC.getTime(currentTime);
  char timeStr[9]; // HH:MM:SS\0 thus 9, c style strings add null_char at end

  //int x = tft.getCursorX();
  //int y = tft.getCursorY();

  //-------  Date ----------
  tft.setCursor(0, 60);
  tft.print(currentTime.getDayOfMonth());
  tft.print("-");
  tft.print(Month2int(currentTime.getMonth()));
  tft.print("-");
  tft.print(currentTime.getYear());

  // ------   Time ------------

  snprintf(timeStr, sizeof(timeStr), "%02u:%02u:%02u",
        currentTime.getHour(),
        currentTime.getMinutes(),
        currentTime.getSeconds()
  );

  tft.setCursor(0,90);
  tft.print(timeStr);
  

  
  //--- Temperature ---------
  tft.setCursor(0, 130);
  tft.print("Temp: ");
  tft.print(thermo.getTemperature());
  tft.print((char)247);
  tft.print(" C ");
  
  //--- DayOfWeek ----------
  String day = getDayOfWeek(currentTime.getDayOfWeek());
  tft.setCursor(0, 160);
  tft.print(day);

  tft.setCursor(0,200);
  if(day=="MONDAY")
  {
    
    tft.print("Start anew with a pure heart.");
  }
  else if(day=="TUESDAY")
  {
    tft.print("Strength comes from stillness.");
  }
  else if(day=="WEDNESDAY")
  {
    tft.print("Compassion is the true power.");
  }
  else if(day=="THURSDAY")
  {
    tft.print("Let go and trust the flow.");
  }
  else if(day=="FRIDAY")
  {
    tft.print("Gratitude lights the path.");
  }
  else if(day=="SATURDAY")
  {
    tft.print("Silence speaks the deepest truths.");
  }
  else if(day=="SUNDAY")
  {
    tft.print("Inner peace is your true home.");
  }


  // --- Delay ------
  delay(200); //200ms


}//end program