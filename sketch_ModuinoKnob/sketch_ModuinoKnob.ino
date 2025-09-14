
/*
  Modulino Knob

*/


#include<Modulino.h>

ModulinoKnob knob;

unsigned int debounceTime = 20;
unsigned int lastDebounceTime = 0;
bool buttonState = 0;    // debounced state
bool lastButtonState = 0; // last raw state

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Modulino.begin();
  knob.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  int position = knob.get();
  bool click = knob.isPressed(); // current raw state

  // check the trigger, when button is pressed
  if(click!=lastButtonState)
  {
    lastDebounceTime = millis();
  }

  // let values stabalise, only then take the buttonState from raw click value.
  if(millis() - lastDebounceTime > debounceTime)
  {
    if(click!=buttonState)
    {
      buttonState = click;
      if(buttonState == HIGH) // only print when button is pressed.
      {
        
        Serial.print("Knob position: ");
        Serial.print(position);
        Serial.println("button pressed");
      }
    }
  }

  // compare only the raw states
  lastButtonState = click;


}
