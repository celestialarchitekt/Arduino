/* Analog In 

  Read a analog value from a pin and blink an LED connected to an output pin.

*/


int sensorPin=A0;
int ledPin=13;
int sensorValue=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue=analogRead(sensorPin);

  digitalWrite(ledPin, HIGH);
  delay(sensorValue);

  digitalWrite(ledPin, LOW);
  delay(sensorValue);



}
