#define front 0
#define back 1
#define right 2
#define left 3
#define inc 4
#define dec 5

#define in1 13
#define in2 12
#define en1 11
#define en2 10
#define in3 7
#define in4 6

int thespeed=85,speed1=85,speed2=85,debounce1=1,debounce2=1,x=0,y=0;

void setup() {
pinMode(front,INPUT);
pinMode(back,INPUT);
pinMode(right,INPUT);
pinMode(left,INPUT);
pinMode(inc,INPUT);
pinMode(dec,INPUT);

pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
}

void loop() {

if (digitalRead(inc) && debounce1){
  thespeed=thespeed+85 ;
  if (thespeed >= 255){thespeed=255;}
  speed1=thespeed;
  speed2=thespeed; 
  debounce1=0;}
else if (digitalRead(dec) && debounce2){
  thespeed = thespeed - 85 ;
  if (thespeed <= 85){thespeed=85;}
  speed1=thespeed;
  speed2=thespeed; 
  debounce2=0;} 
  

  
if (!digitalRead(inc)){debounce1=1;}
if (!digitalRead(dec)){debounce2=1;}
 
analogWrite(en1,speed1-y);
analogWrite(en2,speed2-x);

if(!digitalRead(front) && !digitalRead(left) && !digitalRead(back) && !digitalRead(right))
{digitalWrite(in1,LOW);digitalWrite(in2,LOW);digitalWrite(in3,LOW);digitalWrite(in4,LOW);}

else if (digitalRead(front) && digitalRead(left) && !digitalRead(right) && !digitalRead(back)){
  y=speed2/2;
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);}

else if (digitalRead(back) && digitalRead(left) && !digitalRead(right) && !digitalRead(front)){
  y=speed2/2;
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);}

else if (digitalRead(front) && digitalRead(right) && !digitalRead(left) && !digitalRead(back)){
  x=speed1/2;
    digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);digitalWrite(in4,LOW);}

else if (digitalRead(back) && digitalRead(right) && !digitalRead(left) && !digitalRead(front)){
  x=speed1/2;
    digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
    digitalWrite(in4,HIGH);digitalWrite(in3,LOW);}

else if (digitalRead(front) && !digitalRead(left) && !digitalRead(right) && !digitalRead(back)){
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
  x=0;y=0;}

else if (digitalRead(back) && !digitalRead(left) && !digitalRead(right) && !digitalRead(front)){
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
  x=0;y=0;}

else if (digitalRead(right) && !digitalRead(front) && !digitalRead(back) && !digitalRead(left)){
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
  x=0;y=0;}

else if (digitalRead(left) && !digitalRead(front) && !digitalRead(back) && !digitalRead(right)){
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
  x=0;y=0;}

else if ((digitalRead(front) && digitalRead(back)) || (digitalRead(right) && digitalRead(left))){
  digitalWrite(in1,LOW);digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);digitalWrite(in4,LOW);
  x=0;y=0;}

}
