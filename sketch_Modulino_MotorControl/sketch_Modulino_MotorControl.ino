#include <Modulino.h>

ModulinoKnob knob;

const int motor = 5;          // pin that drives relay or motor driver
const unsigned long debounceTime = 20; // ms

unsigned long lastDebounceTime = 0;
bool buttonState = false;      // latched ON/OFF
bool lastButtonState = false;  // last raw reading
static int level = 1; 

void setup() {
  Serial.begin(9600);
  Modulino.begin();
  knob.begin();
  knob.set(0); 
  pinMode(motor, OUTPUT);
  
}

void loop() {
  
  int position = abs(knob.get());          // knob 0-1023
  //level+=position;
  //if (position < 0) position = 0;    // clamp negative values
  //if (position > 1023) position = 1023;
  int level = (position / 256) + 1;  // 0..1023 → 1..4
  //if (level > 4) level = 4;
  //if (level < 1) level = 1;        // clamp min
  
  int rpmLevel[] = {50,100,150,250};
  int rpm = rpmLevel[level-1];

  
  Serial.print("Position: ");
  Serial.print(position);
  Serial.println();
  Serial.print("Level: ");
  Serial.print(level);
  Serial.println();
  Serial.print("RPM: ");
  Serial.print(rpm);

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


  // If using a relay:
  //digitalWrite(motor, buttonState ? HIGH : LOW);

  // If using a PWM driver:
  analogWrite(motor, buttonState ? rpm : 0);
  
}
