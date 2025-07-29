
#include "RTC.h"

//String name[] = {"mayank", "malhotra"};


String getNameOfMonth(Month month){
  
  switch(month)
  {
    case Month::JANUARY : return "January";
    case Month::FEBRUARY: return "February";
    case Month::MARCH: return "March";
    case Month::APRIL: return "April";
    case Month::MAY: return "May";
    case Month::JUNE: return "June";
    case Month::JULY: return "July";
    case Month::AUGUST: return "August";
    case Month::SEPTEMBER: return "September";
    case Month::OCTOBER: return "October";
    case Month::NOVEMBER: return "November";
    case Month::DECEMBER: return "December";
    

  }
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RTC.begin();

  RTCTime startTime(29, Month::JULY, 2025, 22,54,00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);
  RTC.setTime(startTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  RTCTime currentTime;
  RTC.getTime(currentTime);



  Serial.print(currentTime.getDayOfMonth());
  Serial.print("/");
  Serial.print(getNameOfMonth(currentTime.getMonth()));
  Serial.print("/");
  Serial.println(currentTime.getYear());

}

