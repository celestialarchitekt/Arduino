/*
  Fast WIFI + TFT + Relay + LED control via Webpage
*/

#include "WiFiS3.h"
#include "secret.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>

const int TFT_CS   = 10;
const int TFT_DC   = 9;
const int TFT_RST  = 8;

const int LED = 3;    // LED PWM
const int RELAY = 2;  // Digital relay

unsigned long commandTime = 0;
String lastCommand = "";

Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);
WiFiServer server(80);
int status = WL_IDLE_STATUS;

// -----------------------------------
void showDefaultScreen() {
  tft.fillScreen(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("Hello, Mayank!");
  tft.println("Today is a good day.");
}

// -----------------------------------
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);

  Serial.begin(115200);
  while(!Serial);

  tft.init(20000000); // 20MHz SPI
  tft.setRotation(1);
  showDefaultScreen();

  // Connect Wi-Fi
  while(status != WL_CONNECTED) {
    Serial.print("Attempting to connect...");
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(200);
    Serial.println(status);
  }

  server.begin();
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  

  tft.setCursor(0, 60);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.println("Connected to Wi-Fi");
}

// -----------------------------------
void loop() {
  static char currentLine[128];
  static int idx = 0;

  WiFiClient client = server.available();
  if(client) {
    Serial.println("New client connected");

    while(client.connected() && client.available()) {
      char c = client.read();
      Serial.write(c);

      if(idx < sizeof(currentLine)-1) currentLine[idx++] = c;

      // End of line
      if(c == '\n') {
        currentLine[idx] = '\0';
        idx = 0;

        // Serve HTML
        if(strlen(currentLine) <= 2) {
          client.print(F(
            "HTTP/1.1 200 OK\r\n"
            "Content-type:text/html\r\n"
            "Connection: close\r\n\r\n"
            "<!DOCTYPE HTML><html>"
            "<h1>Command page</h1>"
            "<form action=\"/\" method=\"GET\">"
            "Command: <input type=\"text\" name=\"cmd\">"
            "<input type=\"submit\" value=\"Send\">"
            "</form></html>"
          ));
        }

        // Handle GET /?cmd=
        if(strstr(currentLine, "GET /?cmd=")) {
          char *p = strstr(currentLine, "GET /?cmd=") + 10;
          char cmd[16];
          int i = 0;
          while(*p != ' ' && *p != '\0' && i < 15) cmd[i++] = *p++;
          cmd[i] = '\0';

          Serial.print("Command received: ");
          Serial.println(cmd);

          // Update TFT (only top 50px)
          tft.fillRect(0, 0, tft.width(), 50, ST77XX_WHITE);
          tft.setCursor(0, 0);
          tft.println("Command:");
          tft.println(cmd);

          // LED & Relay
          if(lastCommand != cmd) {
            if(strcmp(cmd, "ON") == 0) {
              analogWrite(LED, 50);       // soft LED
              digitalWrite(RELAY, HIGH);  // relay ON
            } else if(strcmp(cmd, "OFF") == 0) {
              analogWrite(LED, 0);
              digitalWrite(RELAY, LOW);   // relay OFF
            }
            lastCommand = cmd;
          }

          commandTime = millis();
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }

  // Reset TFT after 2s
  if(lastCommand != "" && millis() - commandTime >= 2000) {
    showDefaultScreen();
    lastCommand = "";
  }
}
