/* analog voltage read */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  float voltage;
  
  // analog reading 0 to 1023, get between range 0-5V
  // ADC used is 10bit, 2^10 = 1024 , 0 to 1023 , Vref is 5V by default for arduino
  
  voltage = sensorValue  * (5.0 / 1023.0);
  Serial.println(voltage);

}
