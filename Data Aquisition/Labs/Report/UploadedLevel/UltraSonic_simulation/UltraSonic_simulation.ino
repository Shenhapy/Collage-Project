const int echoPin = 2; 
const int pingPin = 3;  
void setup() 
{ Serial.begin(9600);
  pinMode(pingPin, OUTPUT); pinMode(echoPin, INPUT); }
void loop()
{ long duration, inches, cm; 
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  cm = microsecondsToCentimeters(duration); 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);}
long microsecondsToInches(long microseconds) 
{return microseconds / 74 / 2;}
long microsecondsToCentimeters(long microseconds) 
{return microseconds / 29 / 2;}
