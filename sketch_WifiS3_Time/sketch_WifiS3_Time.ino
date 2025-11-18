#include <WiFiS3.h>
#include "secret.h"
#include "RTC.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S.h>
#include <SPI.h>
#include <Modulino.h>
#include <vector>

WiFiServer server(80);
int status = WL_IDLE_STATUS;
ModulinoThermo thermo;

// TFT Pins
const int TFT_CS   = 10;
const int TFT_DC   = 9;
const int TFT_RST  = 8;
const int TFT_MOSI = 11;
const int TFT_SCK  = 13;
const int TFT_MISO = 12;

Adafruit_ST7796S tft = Adafruit_ST7796S(&SPI, TFT_CS, TFT_DC, TFT_RST);

String getDayOfWeek(DayOfWeek d) {
  static std::vector<String> days = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
  return days[int(d)];
}

String getQuote(String day) {
  if(day=="Monday")    return "Start anew with a pure heart.";
  if(day=="Tuesday")   return "Strength comes from stillness.";
  if(day=="Wednesday") return "Compassion is the true power.";
  if(day=="Thursday")  return "Let go and trust the flow.";
  if(day=="Friday")    return "Gratitude lights the path.";
  if(day=="Saturday")  return "Silence speaks the deepest truths.";
  return "Inner peace is your true home."; // Sunday default
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

  Modulino.begin();
  if (!thermo.begin()) {
    Serial.println("Thermo module not responding");
    while (1);
  }

  RTCTime startTime(18, Month::NOVEMBER, 2025, 14, 30, 0, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);
  RTC.setTime(startTime);

  Serial.println("Connecting to WiFi...");
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(500);
  }

  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started on port 80");
}

void loop() {
  RTCTime currentTime;
  RTC.getTime(currentTime);

  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02u:%02u:%02u",
           currentTime.getHour(),
           currentTime.getMinutes(),
           currentTime.getSeconds());

  // Date
  tft.setCursor(0, 60);
  String dateStr = String(currentTime.getDayOfMonth()) + "-" +
                   String(Month2int(currentTime.getMonth())) + "-" +
                   String(currentTime.getYear());
  tft.print(dateStr);

  // Time
  tft.setCursor(0, 90);
  tft.print(timeStr);

  // Temperature
  tft.setCursor(0, 130);
  tft.print("Temp: ");
  tft.print(thermo.getTemperature());
  tft.print((char)247);
  tft.print(" C");

  // Day
  String day = getDayOfWeek(currentTime.getDayOfWeek());
  tft.setCursor(0, 160);
  tft.print(day);

  // Quote
  tft.setCursor(60, 200);
  tft.print("Quote of the Day");
  tft.setCursor(0, 250);
  tft.print(getQuote(day));

  delay(200);

  // WiFi Server
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected!");
    while (client.connected() && !client.available()) delay(5);

    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);
    client.flush();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<h1>Hello from Arduino WiFiS3</h1>");

    client.stop();
    Serial.println("Client disconnected.");
  }
}
