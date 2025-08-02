/* blink wihtout delay */
// no use of delay() function

const int led_pin = LED_BUILTIN;
const int interval = 1000; //(1sec) delay
unsigned long last_time = 0;
int led_state = LOW;  // initial, LOW is 0, HIGH is 1

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long current_time = millis(); // gives current time in milliseconds

  if(current_time - last_time > interval)
  {
    last_time = current_time;  // dont forget to update last_time
    if(led_state==LOW)
    {
      led_state = HIGH;
    }
      
    else
    {
      led_state = LOW;
    }
      
  }

  digitalWrite(led_pin, led_state);
}
