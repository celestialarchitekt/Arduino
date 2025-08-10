/*
Using a rotary encoder to set brightness of LED

CLK: clock signal  : outputs pulses as we rotate-used to detect movement
DT :  data signal  : works with clock to determine direction of rotation
SW :  switch (push button/toggle)      : detects when knob is moved, usually LOW
+  :  power supply 5V
GND: ground
*/

const uint8_t PIN_CLK = 2;
const uint8_t PIN_DT = 3;
const uint8_t PIN_SW = 4; // button at digital pin 4

const int LED_PIN = 5; // pwm

int lastStateCLK = HIGH;
int ledLevel = 50;
bool ledEnabled = false;
int buttonState = HIGH;

unsigned long debounceTime = 20;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  lastStateCLK = digitalRead(PIN_CLK);
  buttonState = digitalRead(PIN_SW);
  analogWrite(LED_PIN, 0);
}

void loop() {
  int clk = digitalRead(PIN_CLK);
  int dt = digitalRead(PIN_DT);

  // Rotary encoder rotation detection
  if (clk != lastStateCLK) {
    if (digitalRead(PIN_DT) != clk) {
      ledLevel += 5;  // clockwise
    } else {
      ledLevel -= 5;  // counter-clockwise
    }
    ledLevel = constrain(ledLevel, 0, 255);
    Serial.print("Brightness: ");
    Serial.println(ledLevel);
  }
  lastStateCLK = clk;

  // Button debounce & toggle
  int reading = digitalRead(PIN_SW);

  if (reading != buttonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceTime) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        ledEnabled = !ledEnabled;  // toggle on press
        Serial.print("LED Enabled: ");
        Serial.println(ledEnabled);
      }
    }
  }

  // Set LED brightness or off
  analogWrite(LED_PIN, ledEnabled ? ledLevel : 0);
}

