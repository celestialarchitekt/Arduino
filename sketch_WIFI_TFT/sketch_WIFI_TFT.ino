
/*

  Simple WIFI connect and print to TFT, get commands from a Webpage.

*/

#include "WiFiS3.h"
#include "secret.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>
String lastCommand ="";
const int TFT_CS   =  10;
const int TFT_DC   =  9;
const int TFT_RST  =  8;
const int TFT_MOSI =  11;
const int TFT_SCK  =  13;
const int TFT_MISO =  12;

const int LED = 3; // led connected at pin 3
unsigned long commandTime = 0;

// Hardware SPI: MOSI/SCK from ICSP header
Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);


WiFiServer server(80);
int status = WL_IDLE_STATUS;


void showDefaultScreen() {
  tft.fillScreen(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("Hello, Mayank!");
  tft.println("Today is a good day.");
}


void setup() {
  // put your setup code here, to run once:

  pinMode(LED,OUTPUT);

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
  // print IP
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


}






void loop() {
  WiFiClient client = server.available(); // check for incoming clients
  if (client) {
    Serial.println("New Client connected");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        currentLine += c;

        if (c == '\n' && currentLine.length() == 2) { 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML><html>");
          client.println("<h1>Command page</h1>");
          client.println("<form action=\"/\" method=\"GET\">");
          client.println("Command: <input type=\"text\" name=\"cmd\">");
          client.println("<input type=\"submit\" value=\"Send\">");
          client.println("</form>");
          client.println("</html>");
          break;
        }

        if (currentLine.endsWith("\r\n")) {
          if (currentLine.indexOf("GET /?cmd=") >= 0) {
            String cmd = currentLine.substring(currentLine.indexOf("GET /?cmd=") + 10);
            cmd = cmd.substring(0, cmd.indexOf(" "));
            Serial.print("Command received: ");
            Serial.println(cmd);

            // Display command on TFT
            tft.fillScreen(ST77XX_WHITE);
            tft.setCursor(0,0);
            tft.println("Command:");
            tft.println(cmd);

            // LED control
            if(cmd.equals("ON")) {
              lastCommand = "ON";
              analogWrite(LED,50);
            }
            if(cmd.equals("OFF")) {
              lastCommand = "OFF";
              analogWrite(LED,0);
            }

            // Start 2-second timer
            commandTime = millis();
          }
          currentLine = "";
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }

  // --- outside the client block ---
  if(lastCommand != "" && millis() - commandTime >= 2000) {
    showDefaultScreen();
    lastCommand = "";
  }
}
