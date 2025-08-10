
/*
  Read data from computer and control brightness
*/


/*
  Read decimal brightness (0–255) from Serial Monitor and set PWM on ledPin.
  Set Serial Monitor baud to 9600 and "Newline".
*/

const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // On native-USB boards (Leonardo/Micro/SAMD/RP2040), wait for the port:
  while (!Serial) { ; }
  Serial.println("Send a number 0–255 and press Enter");
}

void loop() {
  if (Serial.available()) {
    int value = Serial.parseInt(); // reads a decimal number
    if (value >= 0 && value <= 255) {
      analogWrite(ledPin, value);
      Serial.print("Brightness set to: ");
      Serial.println(value);
    } else {
      // Flush the rest of the line to avoid partial reads
      //while (Serial.available() && Serial.read() != '\n') {}
      //Serial.println("Please enter a value between 0 and 255.");
    }
  }
}

