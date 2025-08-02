/* debounce is the min time taken to accept an input, else the input is rejected as noise */

const int buttonPin = 2;
const int ledPin = 13;

int ledState = HIGH;
int buttonState = LOW;
int lastButtonState = LOW; 


unsigned long lastDebounceTime=0;
unsigned long debounceDelay = 50; // ms


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, ledState); // initially the LED is on
}

void loop() {
  // put your main code here, to run repeatedly:

  int reading = digitalRead(buttonPin);



  // if the state of the switch changed
  if(reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }


  if(millis() - lastDebounceTime > debounceDelay  )
  {
    if(reading != buttonState)
    {
      buttonState=reading;
      if(buttonState==HIGH)
      {
        ledState = !ledState;  // if LED was low it goes to high, if it was high it goes to low
      }
    }
    
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;

}
