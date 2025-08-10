const int button = 7;       // Button input pin
const int led = 9;          // LED output pin (PWM capable)
const unsigned long debounceTime = 5; // Debounce delay in ms

bool ledFlag = false;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  int currentState = digitalRead(button);
  Serial.print("current state: ");
  Serial.println(currentState);

  if(currentState != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if(millis() - lastDebounceTime > debounceTime && currentState==LOW)
  {
    analogWrite(led,50);
  }
  else
  {
    analogWrite(led,0);
  }


  lastButtonState=currentState;
  


}
