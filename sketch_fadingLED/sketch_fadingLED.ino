
/* Fading an LED */




const int ledPin = 9; 

int brightness = 0;
int fadeAmount = 10;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  

}



void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(ledPin, brightness);
  brightness =  brightness + fadeAmount;
  

  if(brightness<=0 || brightness>=255)
  {
    fadeAmount-=10;
    brightness = constrain(brightness,0,255);
  }

  delay(50);
}


/*
  Note: One can also write the logic using two for loops
  
  for(brightnes=0; brightness<=255; brightness++)
  {
    brightness = brightness+fadeAmount;
  }

  for(brightnes=25; brightness>=0; brightness--)
  {
    brightness = brightness+fadeAmount;
  }
*/