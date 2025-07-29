
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  matrix.begin();

  


}

void loop() {
  // put your main code here, to run repeatedly:
 

const uint32_t frame[3] = {
    0b01000000010001100000110001010001,
    0b01000100101001000100010001000100,
    0b00000100010000000100010000000100

  };


  
  matrix.loadFrame(frame);
  delay(500);
}
