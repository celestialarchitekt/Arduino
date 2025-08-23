
/*
  Modulino Thermo
*/


#include <Modulino.h>
ModulinoThermo thermo;

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait till the Serial monitor is ready
  Modulino.begin();
  if (!thermo.begin()) {
    Serial.println("Thermo module not responding");
    while (1); // doesnt let it go to void loop() if INIT fails
  }
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(thermo.getTemperature());
  Serial.print(" °C   Humidity: ");
  Serial.print(thermo.getHumidity());
  Serial.println(" %");
  delay(1000);
}
