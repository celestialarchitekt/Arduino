// Calibration //


const int sensorPin=A0;
const int ledPin=9;



int sensorValue=0;
int sensorMin=1023;  // set as highest. 
int sensorMax=0;    // set as lowest.




void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // calibration starts for first 5000ms or 5sec
  while(millis() < 5000)
  {
    sensorValue=analogRead(sensorPin);

    if(sensorValue > sensorMax)
    {
      sensorMax = sensorValue;
    }

    if(sensorValue < sensorMin)
    {
      sensorMin = sensorValue;
    }

  }

  // calibration ends
  digitalWrite(ledPin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(sensorPin);

  sensorValue=constrain(sensorValue, sensorMin, sensorMax);

  sensorValue=map(sensorValue, 0, 1023, 0, 255);

  analogWrite(ledPin, sensorValue); 


}
