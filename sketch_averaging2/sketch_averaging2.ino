
// set the pin
int inputPin=A0;


// define the variables
int reading=0;
int sum=0;
int count=0;
int average=0;
int sampleCount=10;




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}




void loop() {
  // put your main code here, to run repeatedly:
  
  
  reading = analogRead(inputPin);
  
  sum = sum + reading;
  count++;

  // we want the first 10 values
  if(count>=sampleCount)
  {
    average = sum/sampleCount;
    //reset
    sum=0;
    count=0;
  }

  Serial.print("average: ");
  Serial.print(average);

   
  delay(200);

}
