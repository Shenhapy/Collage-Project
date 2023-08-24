volatile int flow_frequency; float vol = 0.0,l_minute;
unsigned char flowsensor = 2; unsigned long currentTime;unsigned long cloopTime;
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 9);
void flow () {flow_frequency++;}
void setup(){pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH);Serial.begin(9600); lcd.begin(16, 2);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING);
   lcd.clear(); lcd.setCursor(0,0); lcd.print("Water Flow Meter");
   lcd.setCursor(0,1); lcd.print("Circuit Digest");
   currentTime = millis(); cloopTime = currentTime; }
void loop (){currentTime = millis();
   if(currentTime >= (cloopTime + 1000))
   {cloopTime = currentTime; 
    if(flow_frequency != 0){l_minute = (flow_frequency / 7.5);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Rate: ");lcd.print(l_minute);
      lcd.print(" L/M");l_minute = l_minute/60;
      lcd.setCursor(0,1); vol = vol +l_minute; lcd.print("Vol:");  lcd.print(vol);
      lcd.print(" L"); flow_frequency = 0; 
      Serial.print(l_minute, DEC); Serial.println(" L/Sec");}
      else {Serial.println(" flow rate = 0 ");
      lcd.clear();lcd.setCursor(0,0);lcd.print("Rate: ");
      lcd.print( flow_frequency );lcd.print(" L/M");
      lcd.setCursor(0,1);lcd.print("Vol:");lcd.print(vol);lcd.print(" L");}}}
