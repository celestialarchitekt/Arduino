
/* button press LED blink led and debounce */




const int buttonPin=7;
const int ledPin=9; 
const int ledLevel=20;

unsigned long lastDebounceTime=0;
unsigned long debounceTime = 20;

int lastReading=HIGH;
int buttonState=HIGH;


const int blinkInterval=100;
unsigned long lastBlink=0;
bool ledState=false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin,INPUT_PULLUP); 
  pinMode(ledPin,OUTPUT);

}


void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);
  Serial.print("reading: ");
  Serial.println(reading);

  if(reading!=lastReading)
  {
    lastDebounceTime=millis();
    Serial.print("last debounce time: ");
    Serial.println(lastDebounceTime);
  }
  
  if(millis()-lastDebounceTime>debounceTime)
  {
    if(reading!=buttonState)
    {
      Serial.print("button state: ");
      Serial.println(buttonState);
      buttonState=reading;
      Serial.print("button state: ");
      Serial.println(buttonState);
    }
  }


  lastReading=reading;


  
  //analogWrite(ledPin, buttonState==LOW ? ledLevel :0);

  // Logic 1. blink the LED, delay() freezed the code, blocking function.

  /*
  if(buttonState==LOW)
  {
    analogWrite(ledPin,30);
    delay(100);
    analogWrite(ledPin,0);
    delay(100);
  }
 */

   // Logic 2. blink LED using millis

  if(buttonState==LOW)
  {
    if(millis()-lastBlink>=blinkInterval) // time to toggle 
    {
      ledState=!ledState;
      lastBlink=millis();
      analogWrite(ledPin, ledState? ledLevel: 0); // if ledState=HIGH , given ledLevel else 0
    }
  }
  else
  {
    analogWrite(ledPin,0);
    lastBlink=millis();
    ledState=0;
  }

}
