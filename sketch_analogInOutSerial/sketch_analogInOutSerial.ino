
/* analog in, analog out, serial out*/


const int analogPin=A0;
const int analogOutPin=9;  


int sensorValue=0;
int outputValue=9;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(analogPin);
  outputValue=map(sensorValue,0,1023,0,255);
  
  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor= ");
  Serial.print(sensorValue);
  Serial.print("Output= ");
  Serial.print(outputValue);

  delay(2); // 2ms to next read

}
