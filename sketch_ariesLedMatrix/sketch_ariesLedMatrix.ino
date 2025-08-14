
#include"Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  byte aries[8][12] =
  {
    {0,0,1,0,0,0,0,0,0,1,0,0},
    {0,1,0,1,0,0,0,0,1,0,1,0},
    {1,0,0,0,1,0,1,0,0,0,0,1},
    {0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0}
  };

  matrix.renderBitmap(aries,8,12);


}
