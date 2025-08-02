
// Fading an LED using PWM //


int led = 9;  // pin 9 is a pwm pin
int brightness = 0;
int fadeAmount = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, brightness); // since pin9 is pwm, we can change the magnitude
  brightness+= fadeAmount;

  if(brightness<= 0 || brightness >=255)
  {
    fadeAmount = -fadeAmount;
  }

  delay(30); // delay between two writes

}
