
// Moving Average //

const int windowSize = 10;
int buffer[windowSize];
int head = 0;
int total=0;
int average=0;

void setup()
{
  // init the buffer array with zeroes
  for(int i= 0; i<windowSize; i++)
  {
    buffer[i] = 0;
    total = total+buffer[i];

  }

  Serial.begin(9600);
}


void loop()
{
  int reading = analogRead(A0);


  total -= buffer[head];
  buffer[head] = reading;
  total = total + reading;

  head = (head+1)%windowSize;  // head resets after 10 -> 0

  average = total/windowSize;

  Serial.println(average);


}