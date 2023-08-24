#include<LiquidCrystal.h>
#define front 0
#define back 1
#define right 2
#define left 3
#define inc 4
#define dec 5

int speed1=85,debounce1=1,debounce2=1;

LiquidCrystal lcd(13,12,11,10,9,8);

void setup() {
lcd.begin(16,2);
lcd.setCursor(0,0);lcd.print("Speed m");
lcd.setCursor(0,1);lcd.print("Dir. ");

pinMode(front,INPUT);
pinMode(back,INPUT);
pinMode(right,INPUT);
pinMode(left,INPUT);
pinMode(inc,INPUT);
pinMode(dec,INPUT);
}

void loop() {

  if (digitalRead(inc) && debounce1){
  speed1=speed1+85 ;
  if (speed1 >= 255){speed1=255;}
  debounce1=0;}
else if (digitalRead(dec) && debounce2){
  speed1 = speed1 - 85 ;
  if (speed1 <= 85){speed1=85;}
  debounce2=0;} 

if (!digitalRead(inc)){debounce1=1;}
if (!digitalRead(dec)){debounce2=1;}


if (speed1 == 85){lcd.setCursor(7,0);lcd.print("in  ");}
else if (speed1 == 170){lcd.setCursor(7,0);lcd.print("id  ");}
else if (speed1 == 255){lcd.setCursor(7,0);lcd.print("ax  ");}
else {lcd.setCursor(7,0);lcd.print("out ");}

if(!digitalRead(front) && !digitalRead(left) && !digitalRead(back) && !digitalRead(right))
{lcd.setCursor(6,1);lcd.print("stop ");}

else if (digitalRead(front) && digitalRead(left)){
lcd.setCursor(6,1);lcd.print("F.L  ");}

else if (digitalRead(back) && digitalRead(right)){
lcd.setCursor(6,1);lcd.print("B.R  ");}

else if (digitalRead(front) && digitalRead(right)){
lcd.setCursor(6,1);lcd.print("F.R  ");}

else if (digitalRead(back) && digitalRead(left)){
lcd.setCursor(6,1);lcd.print("B.L  ");}
  
else if (digitalRead(front) && !digitalRead(left) && !digitalRead(right)){
lcd.setCursor(6,1);lcd.print("front");}

else if (digitalRead(back) && !digitalRead(left) && !digitalRead(right)){
lcd.setCursor(6,1);lcd.print("back ");}

else if (digitalRead(right) && !digitalRead(front) && !digitalRead(back)){
lcd.setCursor(6,1);lcd.print("right");}

else if (digitalRead(left) && !digitalRead(front) && !digitalRead(back)){
lcd.setCursor(6,1);lcd.print("left ");}

else if ((digitalRead(right) && digitalRead(left)) || (digitalRead(front) && digitalRead(back))){
lcd.setCursor(6,1);lcd.print("error");}
}
