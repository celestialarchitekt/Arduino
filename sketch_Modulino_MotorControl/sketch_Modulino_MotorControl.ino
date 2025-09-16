#include <Modulino.h>

ModulinoKnob knob;

const int motor = 5;          // pin that drives relay or motor driver
const unsigned long debounceTime = 20; // ms

unsigned long lastDebounceTime = 0;
bool buttonState = false;      // latched ON/OFF
bool lastButtonState = false;  // last raw reading

void setup() {
  Serial.begin(9600);
  Modulino.begin();
  knob.begin();
  pinMode(motor, OUTPUT);
}

void loop() {
  int position = knob.get();          // knob 0-1023
  bool click   = knob.isPressed();    // raw button state

  if (click != lastButtonState) {
    lastDebounceTime = millis();      // reset debounce timer
  }

  Serial.print("click = ");
  Serial.print(click);
  Serial.print("  lastButtonState = ");
  Serial.println(lastButtonState);

  if ((millis() - lastDebounceTime > debounceTime) &&
      click == HIGH && lastButtonState == LOW) {
    // rising edge: button was just pressed
    buttonState = !buttonState;       // toggle ON/OFF
    Serial.print("Button: ");
    Serial.println(buttonState);
  }

  lastButtonState = click;            // save raw state for next loop

  // ---- Drive the motor or relay ----
  int speed = map(position, 0, 1023, 0, 255);

  // Divide into levels

  // If using a relay:
  //digitalWrite(motor, buttonState ? HIGH : LOW);

  // If using a PWM driver:
  analogWrite(motor, buttonState ? speed : 0);
  Serial.print("Speed: ");
  Serial.print(speed);
}
