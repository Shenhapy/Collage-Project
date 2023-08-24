#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);
int redled=1,greenled=2,pump=3,button=4,fire;

void setup() {
lcd.begin(16,2);
pinMode(redled,OUTPUT);
pinMode(greenled,OUTPUT);
pinMode(pump,OUTPUT);
pinMode(button,INPUT);
pinMode(5,OUTPUT);
}

void loop() {
  fire=!digitalRead(button);

  if (fire)
  {
  lcd.setCursor(4,0);
  lcd.print("fire");
  digitalWrite(redled,HIGH);
  digitalWrite(pump,HIGH);
  digitalWrite(greenled,LOW);
  digitalWrite(5,HIGH);
  }
  else
  {
  lcd.setCursor(4,0);
  lcd.print("safe");
  digitalWrite(redled,LOW);
  digitalWrite(pump,LOW);
  digitalWrite(greenled,HIGH);  
  digitalWrite(5,LOW);
  }
  
}
