
// button settings
const int button = 7;       // Button input pin
const int led = 9;          // LED output pin (PWM capable)

// flags
bool ledFlag = false;
int lastButtonState = HIGH;

// timers
unsigned long lastDebounceTime = 0;
const unsigned long debounceTime = 5; // Debounce delay in ms
unsigned long lastBlink = 0;
unsigned long blinkInterval=500;




void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}




void loop() {


  int currentState = digitalRead(button);

/*
  if(currentState != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime > debounceTime))
  {
    if(currentState==LOW )
    {
      ledFlag = true;
    }else{
      ledFlag=false;
    }
  }

*/


  //lastButtonState=currentState;
  //analogWrite(led, ledFlag?50:0); // ledFlag->true, ledFlag=false


  if(millis() - lastDebounceTime > debounceTime && currentState==LOW)
  {
    if(millis() - lastBlink > blinkInterval)
    {
        ledFlag = !ledFlag;
        lastBlink = millis();
     
    }
  }else
  {
    ledFlag = false;
    lastBlink=0;
  }


  analogWrite(led, ledFlag? 50 :0); // ledFlag->true, ledFlag=false
  lastButtonState=currentState;



  /*
  if(millis() - lastDebounceTime > debounceTime && currentState==LOW)
  {
    analogWrite(led,50);
  }
  else
  {
    analogWrite(led,0);
  }
  */

  
  

} // end of program
