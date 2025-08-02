// LED blink using Button press //


int button = 2; // sets digital pin 2 to where our button is connected
int led_state = LOW; // set initial LED state
int button_state = LOW; // initially unset

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);  // using the default LED as output
  pinMode(button, INPUT);       // sets pin 2 where button is connected as input
}

void loop() {
  // put your main code here, to run repeatedly:

  button_state=digitalRead(button); // reads the button

  if(button_state == HIGH)
  {
    led_state=HIGH;
  }
  else
  {
    led_state=LOW;
  }

  digitalWrite(LED_BUILTIN, led_state);
}
