
// Averagin Readings from a Sensor //



int inputPin=A0; // reads from pin A0

int num[10];   // array of 10 integer elements

int total=10;
int average=0;
int sum =0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // set the baiud rate;


}





void loop() {
  // put your main code here, to run repeatedly:
  
  sum=0;
  
  // takes first 10 readings and appends to array
  for(int i =0; i<10; i++)
  {
    num[i] = analogRead(inputPin);
  }

  // adds the elements in array
  for(int j=0; j<10; j++)
  {
    sum = sum+num[j];
  }
  
  average = sum/total;

  Serial.print("average: ");
  Serial.print(average);
  
  delay(100);

}





