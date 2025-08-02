// State Change Detection //


const int buttonPin = 2;
const int ledPin = 13;

int buttonPushCounter=0;
int buttonState = LOW;
int lastButtonState=LOW;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(buttonPin);

  if(buttonState !=lastButtonState)
  {
    if(buttonState==HIGH)
    {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    }
    Serial.println("off");
    delay(50); // avoid debouncing, waits 50ms to read the next buttonState
  }

  // dont forget to update the button state
  lastButtonState = buttonState;


  if(buttonPushCounter%4 ==0)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }

}
