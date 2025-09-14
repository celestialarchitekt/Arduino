
/*

  Simple WIFI connect and print to TFT

*/

#include "WiFiS3.h"
#include "secret.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>

const int TFT_CS   =  10;
const int TFT_DC   =  9;
const int TFT_RST  =  8;
const int TFT_MOSI =  11;
const int TFT_SCK  =  13;
const int TFT_MISO =  12;

// Hardware SPI: MOSI/SCK from ICSP header
Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);


WiFiServer server(80);
int status = WL_IDLE_STATUS;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){;} // wait for serial port to connect

  tft.init(8000000); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("Hello, Mayank!");
  tft.println("Today is a good day.");



  while(status != WL_CONNECTED)
  {
      

      Serial.print("attempting to connect...");
      status = WiFi.begin(SECRET_SSID,SECRET_PASS);
      delay(10000); // 10ms wait

      Serial.print("Status: ");
      Serial.print(status);
  }

  // when connected
  server.begin();
  Serial.println();
  Serial.println("connected");
  tft.println("Arduino connected to Wifi.");
  // call function

}

void loop() {
  // put your main code here, to run repeatedly:

}
