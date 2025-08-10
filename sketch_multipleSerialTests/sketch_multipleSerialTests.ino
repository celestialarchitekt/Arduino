
/*multiple serial test*/

/*

Serial -> usb port connected to PC
Serial1 -> Tx/Rx port ; for loopback short them

*/

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read from port1 and write to port0
  if(Serial1.available()>0)
  {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port0 and write to port1
  if(Serial.available()>0)
  {
    int x = Serial.read();
    Serial1.write(x);
  }

}
