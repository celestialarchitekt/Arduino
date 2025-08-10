
/*
 Set LED using SerialInput
 
*/


const int ledPin=9;
int incomingByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0)
  {
    incomingByte=Serial.read();

    if(incomingByte=='h')
    {
      analogWrite(ledPin, 50);
    }

    if(incomingByte=='l')
    {
      analogWrite(ledPin,10);
    }
    
  }



}
