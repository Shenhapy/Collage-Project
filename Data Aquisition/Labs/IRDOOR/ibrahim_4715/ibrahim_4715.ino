#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);
int ir=1,o=2,c=3,opening=4,closing=5;

void setup() {lcd.begin(16,2);
pinMode(opening,OUTPUT); pinMode(closing,OUTPUT);
pinMode(ir,INPUT); pinMode(o,INPUT); pinMode(c,INPUT);}

void loop() {
if(digitalRead(ir) && !digitalRead(o)){digitalWrite(opening,HIGH);digitalWrite(closing,LOW);
lcd.clear();lcd.setCursor(1,0);lcd.print("Opening");}

else if (!digitalRead(ir) && !digitalRead(c)){digitalWrite(closing,HIGH);digitalWrite(opening,LOW);
lcd.clear();lcd.setCursor(1,0);lcd.print("Closing");}

else if (digitalRead(o) && digitalRead(ir)){digitalWrite(closing,LOW);digitalWrite(opening,LOW);
lcd.clear();lcd.setCursor(1,0);lcd.print("Fully Opened");}

else if (digitalRead(c) && !digitalRead(ir)){digitalWrite(closing,LOW);digitalWrite(opening,LOW);
lcd.clear();lcd.setCursor(1,0);lcd.print("Fully Closed");}

while (digitalRead(c) && digitalRead(o)){digitalWrite(closing,LOW);digitalWrite(opening,LOW);
lcd.clear();lcd.setCursor(1,0);lcd.print("Sensors Problem");}
}

