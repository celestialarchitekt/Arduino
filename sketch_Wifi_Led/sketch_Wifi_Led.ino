#include <WiFiS3.h>
#include "secret.h"

WiFiServer server(80);

const int controlPin = 5;  // the pin you want to control

void setup() {
  Serial.begin(9600);

  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW);

  Serial.println("Connecting to WiFi...");
  while (WiFi.begin(SECRET_SSID, SECRET_PASS) != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (!client) return;

  // Wait for data from browser
  while (client.connected() && !client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();

  // Process command from form
  if (req.indexOf("command=HIGH") != -1) {
    digitalWrite(controlPin, HIGH);
    Serial.println("Pin set HIGH");
  }
  if (req.indexOf("command=LOW") != -1) {
    digitalWrite(controlPin, LOW);
    Serial.println("Pin set LOW");
  }

  // Send HTML form
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<html><body style='font-family:Arial;'>");
  client.println("<h1>Arduino Pin Control</h1>");

  client.println("<form action='/' method='GET'>");
  client.println("Command: <input type='text' name='command' placeholder='HIGH or LOW'>");
  client.println("<input type='submit' value='Send'>");
  client.println("</form>");

  client.println("<p>Pin 5 is now: ");
  client.print((digitalRead(controlPin) == HIGH) ? "HIGH" : "LOW");
  client.println("</p>");

  client.println("</body></html>");

  client.stop();
}

