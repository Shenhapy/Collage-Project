#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

int sensor=A5,pot=A1,ldr=A2;
float temp;

void setup() {lcd.begin(16,2);}

void loop() {lcd.clear();

lcd.setCursor(0,0);lcd.print("Temp=");
lcd.setCursor(6,0);lcd.print((analogRead(sensor)-5)/2.0);
//Different formula but it works for my simulation
//I think there is error in my protus version

lcd.setCursor(0,1);lcd.print("Pot=");
lcd.setCursor(4,1);lcd.print(analogRead(pot)*100.0/1023.0);

lcd.setCursor(8,1);lcd.print("LDR=");
lcd.setCursor(12,1);lcd.print(analogRead(ldr)*100.0/1023.0); 
//this one worked when i changed the the values of ldr
delay(500);}
