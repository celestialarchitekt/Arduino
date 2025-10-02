
const int CLK = 2;
const int DT = 3;
const int SW = 4;
const int LED = 5; // PWM pin

unsigned long debounceTime = 20; // ms
unsigned long lastDebounceTime_rotor = 0;
unsigned long lastDebounceTime_button = 0;

int brightness = 0;
int lastClkState;
int lastButtonState=HIGH;
int button_state=HIGH;
bool led_status = false;

void setup() {
  Serial.begin(9600);

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  lastClkState = digitalRead(CLK);
  lastButtonState = digitalRead(SW);
}

void loop() {
  // ---- Rotary encoder ----
  int currentClkState = digitalRead(CLK);
  int currentDTState  = digitalRead(DT);


  if (led_status) { // only work when LED is ON
    if ((currentClkState == HIGH && lastClkState == LOW) &&
        (millis() - lastDebounceTime_rotor > debounceTime)) {
        
      if (currentDTState != currentClkState) {
        brightness += 5;
      } else {
        brightness -= 5;
      }
      brightness = constrain(brightness, 0, 255);
      lastDebounceTime_rotor = millis();
    }
  }
  lastClkState = currentClkState;

  // ---- Button ----
 int reading = digitalRead(SW);

// detect a change in button state
if (reading != lastButtonState) {
    lastDebounceTime_button = millis();
}

if ((millis() - lastDebounceTime_button) > debounceTime) {
    // if the button state has changed and it's now pressed
    if(reading!=button_state)
    {
      button_state=reading;
      if(button_state==LOW)
      {
        brightness=20;
        led_status =!led_status;
      }
    }
}

// remember the current state
lastButtonState = reading;
 

  // ---- Output ----
  analogWrite(LED, led_status ? brightness : 0);
}

