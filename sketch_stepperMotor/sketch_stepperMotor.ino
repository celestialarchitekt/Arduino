/*
 red = 5V 
 brown = gnd
 orange = signal = pwm or output pin
*/


#include <Servo.h>
Servo myServo;

void setup() {
myServo.attach(6); // pwm pin


}

void loop() {


 myServo.write(0);
 delay(1000);
 myServo.write(20);
 delay(1000);
 myServo.write(40);
 delay(1000);

}