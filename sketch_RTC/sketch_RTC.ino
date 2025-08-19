
/*

RTCTime is the class,
startTime() an object created and args constructor called,
setTime() is a method and takes an object of class RTCTime ,
getTime() is a method and takes an object of class RTCTime

*/


#include "RTC.h"


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



  Serial.begin(9600);

  RTC.begin();
  
  // Write once, upload, then comment and then upload again
  /*  

  RTCTime startTime(19, //day
  Month::AUGUST,        // month
  2025,                 // year
  19, 53, 00,          // time
  DayOfWeek::TUESDAY,   // day
  SaveLight::SAVING_TIME_ACTIVE);

  RTC.setTime(startTime);
  */

}



void loop() {
  // put your main code here, to run repeatedly:

  
  RTCTime currentTime;
  RTC.getTime(currentTime);

  Serial.print(currentTime.getDayOfMonth());
  Serial.print("-");
  Serial.print(Month2int(currentTime.getMonth()));
  Serial.print("-");
  Serial.print(currentTime.getYear());
  Serial.println();

  Serial.print("Day of Week: ");
  String day = getDayOfWeek(currentTime.getDayOfWeek());
  Serial.print(day);
  Serial.println();

  Serial.print(currentTime.getHour());
  Serial.print(":");
  Serial.print(currentTime.getMinutes());
  Serial.print(":");
  Serial.print(currentTime.getSeconds());

  Serial.println();
  //Unix timestamp
  //Serial.print("Unix timestamp: ");
  //Serial.println(currentTime.getUnixTime());

  Serial.println();

  delay(1000); //1sec or 1000ms



}









