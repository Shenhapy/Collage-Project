#include<LiquidCrystal.h>
LiquidCrystal lcd(5,4,3,2,1,0);

#define front A5
#define back A4
#define right A3
#define left A2
#define inc A1
#define dec A0

#define in1 13
#define in2 12
#define en1 11
#define en2 10
#define in3 9
#define in4 8

int speed1=85,debounce1=1,debounce2=1;

void setup() {
lcd.begin(16,2);
lcd.setCursor(0,0);lcd.print("Speed m");
lcd.setCursor(0,1);lcd.print("Dir. ");

pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
}

void loop() {

if (digitalRead(inc) && debounce1){
  speed1=speed1+85 ;
  if (speed1 > 255){speed1=255;}
  debounce1=0;}
else if (digitalRead(dec) && debounce2){
  speed1 = speed1 - 85 ;
  if (speed1 < 85){speed1=85;}
  debounce2=0;} 

if (!digitalRead(inc)){debounce1=1;}
if (!digitalRead(dec)){debounce2=1;}

if (speed1 == 85){lcd.setCursor(7,0);lcd.print("in  ");}
else if (speed1 == 170){lcd.setCursor(7,0);lcd.print("id  ");}
else if (speed1 == 255){lcd.setCursor(7,0);lcd.print("ax  ");}
else {lcd.setCursor(7,0);lcd.print("an error");}

if(!digitalRead(front) && !digitalRead(back) && !digitalRead(left) && !digitalRead(right))
{digitalWrite(in1,LOW);digitalWrite(in2,LOW);digitalWrite(in3,LOW);digitalWrite(in4,LOW);
 lcd.setCursor(6,1);lcd.print("stop ");}

else if (digitalRead(front) && !digitalRead(back) && digitalRead(left) && !digitalRead(right)){
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
  analogWrite(en1,speed1*0.5);
  analogWrite(en2,speed1);
  lcd.setCursor(6,1);lcd.print("F.L  ");}

else if (!digitalRead(front) && digitalRead(back) && digitalRead(left) && !digitalRead(right)){
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
  analogWrite(en1,speed1*0.5);
  analogWrite(en2,speed1);
  lcd.setCursor(6,1);lcd.print("B.L  ");}

else if (digitalRead(front) && !digitalRead(back) && !digitalRead(left) && digitalRead(right)){
    digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
    analogWrite(en1,speed1);
    analogWrite(en2,speed1*0.5);
    lcd.setCursor(6,1);lcd.print("F.R  ");}

else if (!digitalRead(front) && digitalRead(back) && !digitalRead(left) && digitalRead(right)){
    digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
    digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
    analogWrite(en1,speed1);
    analogWrite(en2,speed1*0.5);
    lcd.setCursor(6,1);lcd.print("B.R  ");}

else if (digitalRead(front) && !digitalRead(back) && !digitalRead(left) && !digitalRead(right)){
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
  analogWrite(en1,speed1);analogWrite(en2,speed1);
  lcd.setCursor(6,1);lcd.print("front");}

else if (!digitalRead(front) && digitalRead(back) && !digitalRead(left) && !digitalRead(right)){
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
  analogWrite(en1,speed1);analogWrite(en2,speed1);
  lcd.setCursor(6,1);lcd.print("back ");}

else if (!digitalRead(front) && !digitalRead(back) && digitalRead(left) && !digitalRead(right)){
  digitalWrite(in2,HIGH);digitalWrite(in1,LOW);
  digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
  analogWrite(en1,speed1-40);analogWrite(en2,speed1-40); //slower rotational speed for better control
  lcd.setCursor(6,1);lcd.print("left ");}

else if (!digitalRead(front) && !digitalRead(back) && !digitalRead(left) && digitalRead(right)){
  digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);digitalWrite(in3,LOW);
  analogWrite(en1,speed1-40);analogWrite(en2,speed1-40); //slower rotational speed for better control
  lcd.setCursor(6,1);lcd.print("right");}

else if ((digitalRead(front) && digitalRead(back)) || (digitalRead(right) && digitalRead(left)))
{digitalWrite(in1,LOW);digitalWrite(in2,LOW);digitalWrite(in3,LOW);digitalWrite(in4,LOW);
 lcd.setCursor(6,1);lcd.print("error");}
}
