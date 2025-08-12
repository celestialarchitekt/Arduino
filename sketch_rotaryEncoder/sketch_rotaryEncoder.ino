const int PIN_CLK = 2;
const int PIN_DT  = 3;
const int PIN_SW  = 4;

long counter = 0;
int lastCLKState;

unsigned long lastDebounceTime=0;
unsigned long DebounceTime=20;



void setup() {
  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT,  INPUT_PULLUP);
  pinMode(PIN_SW,  INPUT_PULLUP);

  Serial.begin(9600);

  lastCLKState = digitalRead(PIN_CLK);
}

void loop() {
  int clkState = digitalRead(PIN_CLK);

  // Detect a change in CLK , rising edge and debounce
  if ((clkState == HIGH && lastCLKState==LOW) && (millis()-lastDebounceTime)>DebounceTime) 
  {

    // If DT state is different from CLK, it's CW
    if (digitalRead(PIN_DT) != clkState) {
      counter++;
    } else {
      counter--;
    }

    Serial.print("Counter: ");
    Serial.println(counter);
     lastDebounceTime=millis();
  }
 
  lastCLKState = clkState;
}


/* 
NOTE: if we use

if(clkState!=lastClkState)
-> it checks for rise and fall edge in one pulse, counter will be incremented twice


*/

