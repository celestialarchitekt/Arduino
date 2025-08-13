
/*

RELAY MOTOR CONTROL and LED

*/


const int relay1=12; // NO- normally open
const int button=13;
const int led=9; // pwm

int buttonStableState=HIGH;
int lastButtonState=HIGH;
bool fanStatus=false;
bool ledStatus=false;

/*
NOTE: 
NO: normally open : disconnected from COM when relay is OFF. Device will be OFF be default and triggered when relay is called.

COM: moving contact inside the relay, input to the relay. It moves between NO and NC.

NC: normally closed: conncted to COM when relay is OFF. Device will be ON be default and OFF when relay is triggered.

RELAY is active HIGH, meaning HIGH->energised and LOW->de-energised
*/

unsigned long lastDebounceTime=0;
const unsigned long debounceTime=20;




void setup() {
  // put your setup code here, to run once:

  pinMode(relay1,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  
 
}




void loop() {
  // put your main code here, to run repeatedly:


  int reading = digitalRead(button);
  
  if(reading!=lastButtonState)
  {
    lastDebounceTime=millis();
  }


  if(millis()-lastDebounceTime>debounceTime)
  {
    if(reading!=buttonStableState)
    {
    buttonStableState=reading;

      if(buttonStableState==LOW)
      {
        fanStatus=!fanStatus;
        ledStatus=!ledStatus;
        
      }
    }
  }

  lastButtonState=reading;

  digitalWrite(relay1, fanStatus?HIGH:LOW);
  analogWrite(led, ledStatus?50:0);

}//end
