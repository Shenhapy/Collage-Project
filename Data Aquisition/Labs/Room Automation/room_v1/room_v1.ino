#include <Keypad.h>
#include<LiquidCrystal.h>

//lcd
#define rs 53
#define e 52
#define d4 51
#define d5 50
#define d6 49
#define d7 48
LiquidCrystal lcd(rs,e,d4,d5,d6,d7);
 

//keypad
#define pwlength 8
int i=0,j=0,m=0,k=0;
char key;
boolean flag,xflag=false;
char password[pwlength+1],confirmpw[pwlength+1];
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
#define rd 45
#define rc 44
#define rb 43
#define ra 42
#define c1 41
#define c2 40
#define c3 39
byte rowPins[ROWS] = {ra, rb, rc, rd}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {c1, c2, c3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//fire pins
#define firein 38
#define flamesense 21
#define firebuzz 30

//door pins
#define f1 47
#define r1 46
#define opened 37
#define closed 36
#define leave 32

//ir sensor
#define ir 34

//temperature
#define temp A14
#define fanspeed 7

//ldr
#define ldr A15
#define led1 22
#define led2 23
#define led3 24
#define led4 25

#define theif 27

void setup() {
lcd.begin(20,4);

//inputs
 pinMode(ir,INPUT);
 pinMode(flamesense,INPUT);
 pinMode(opened,INPUT);
 pinMode(closed,INPUT); 
 pinMode(leave,INPUT);

//outputs
 pinMode(f1,OUTPUT);
 pinMode(r1,OUTPUT);
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(firein,OUTPUT);
 pinMode(fanspeed,OUTPUT);
 pinMode(theif,OUTPUT);
 pinMode(firebuzz,OUTPUT);
//check all fire state first! 
 fire();
 attachInterrupt(digitalPinToInterrupt(flamesense), fire , CHANGE);

//opening message
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Hello Sir");
  lcd.setCursor(0,1);lcd.print("Room Automation");
  lcd.setCursor(0,2);lcd.print("By 4715");
  lcd.setCursor(0,3);lcd.print("Let's Start!");
  delay(500);

//set passcode for first time
  setpw();

//enter passcode to enter
  checkpw();
  delay(200);
  lcd.clear();

//check fire as it used by interput
fire();
lcd.setCursor(5,3);lcd.print("Press# rest PW");
}

void loop() {
j=0; //counter of trials
//to reset pw later it already entered it correct
key = keypad.getKey();
if (key == '#')
{setpw();
  lcd.clear();
  lcd.setCursor(5,3);lcd.print("Press# rest PW");
  delay(500);
  fire();}    
//door auto opening and closing
door();
//check the presenct to actiate the ldr and temp sense options
ircheck();   
}

void ircheck(){
 if (digitalRead(ir)){ 
 lcd.setCursor(12,0);lcd.print(" Occpied");
 tempcontrol();
 ldrcontrol();}
else {lcd.setCursor(12,0);lcd.print(" Empty  ");analogWrite(fanspeed,0);
      ledoff();}
}

void fire(){
if(digitalRead(flamesense))
{lcd.setCursor(0,3);lcd.print("fire                      ");digitalWrite(firein,HIGH);digitalWrite(firebuzz,HIGH);}
else {lcd.setCursor(0,3);lcd.print("safe                   ");digitalWrite(firein,LOW);digitalWrite(firebuzz,LOW);}
}

void door(){
int closeread,openread,irread;
closeread=digitalRead(closed);openread=digitalRead(opened);irread=digitalRead(ir);
lcd.setCursor(0,0);lcd.print("Door ");
if (flag && closeread && !irread)                        {digitalWrite(f1,HIGH);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Opening");} //door opens after put password
if (flag && openread &&  !irread)                        {digitalWrite(f1,LOW);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Opened ");} //door full opened
if (flag && openread &&   irread)                        {digitalWrite(f1,LOW);digitalWrite(r1,HIGH);
lcd.setCursor(5,0);lcd.print("Closing");} //get in so door closing
if (flag && closeread &&  irread && !digitalRead(leave)) {digitalWrite(f1,LOW);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Closed ");} //door fully closed
if (closeread && irread && digitalRead(leave)){flag=false;digitalWrite(f1,HIGH);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Opening");} //door opening to leave
if (!flag && openread && irread)                         {digitalWrite(f1,LOW);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Opened ");} // door fully open to leave
if (!flag && openread && !irread)                        {digitalWrite(f1,LOW);digitalWrite(r1,HIGH);
lcd.setCursor(5,0);lcd.print("Closing");} //door closing after left
if (!flag && closeread && !irread)                       {digitalWrite(f1,LOW);digitalWrite(r1,LOW);
lcd.setCursor(5,0);lcd.print("Locked "); delay(500);
checkpw();} //door is fully closed and u left
}


void tempcontrol(){
  int thespeed,thetemp;
  thetemp=(analogRead(temp)/2)-1;
  lcd.setCursor(0,1);lcd.print("TEMP ");
  lcd.setCursor(5,1);lcd.print(thetemp);
     if (thetemp<25){thespeed=0;lcd.setCursor(7,1);lcd.print(" Fan Stop");}
     else if (thetemp<30 && thetemp>24){thespeed=195;lcd.setCursor(7,1);lcd.print(" Fan LOW ");}
     else if (thetemp<35 && thetemp>29){thespeed=225;lcd.setCursor(7,1);lcd.print(" Fan Mid ");}
     else {thespeed=255;lcd.setCursor(7,1);lcd.print(" Fan HIGH");}
  analogWrite(fanspeed,thespeed);
  }

void ldrcontrol(){
  int lightlevel;
  lightlevel=(analogRead(ldr)*10/1023);
  if (lightlevel == 10){lightlevel=9;}
  lcd.setCursor(0,2);lcd.print("Light Level ");
  lcd.setCursor(12,2);lcd.print(lightlevel);
   if (lightlevel<2){digitalWrite(led1,HIGH);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
   lcd.setCursor(14,2);lcd.print(" 4 LED");}
   else if (lightlevel<4 && lightlevel>1){digitalWrite(led1,LOW);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
   lcd.setCursor(14,2);lcd.print(" 3 LED");}
   else if (lightlevel<6 && lightlevel>3){digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
   lcd.setCursor(14,2);lcd.print(" 2 LED");}
   else if (lightlevel<8 && lightlevel>5){digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,HIGH);
   lcd.setCursor(14,2);lcd.print(" 1 LED");}
   else {ledoff();lcd.setCursor(14,2);lcd.print(" 0 LED");}}
void ledoff(){digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,LOW);
}

void setpw(){
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Set Password...");
  lcd.setCursor(0,1);lcd.print("3 Till 8 numbers");
  lcd.setCursor(0,3);lcd.print("confirm # , delete *");
  flag=true;
  m=0;
  k=0;
  while (k<pwlength){
  key = keypad.getKey();
  if (key && key!='*' && key!='#'){
  k++;
  m++;
  password[k]= key;
  lcd.setCursor(k,2);lcd.print(password[k]);}
  else if (key == '#' && k>2){k=pwlength;}
  else if (key == '*' && k>0){lcd.setCursor(k,2);lcd.print(" ");k--;m--;}
  }
  delay(200);  
  confirmpww();
  }

void confirmpww(){  
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Confirm Password...");
  lcd.setCursor(0,1);lcd.print("3 Till 8 numbers");
  lcd.setCursor(0,3);lcd.print("confirm # , delete *");
  k=0;
  while (k<pwlength){
  key = keypad.getKey();
  if (key && key!='*' && key!='#'){
  k++;
  confirmpw[k]= key;
  lcd.setCursor(k,2);lcd.print(confirmpw[k]);}
  if (key == '#' && k>2){if (m != k){flag=false;}k=pwlength;}
  else if (key == '*' && k>0){lcd.setCursor(k,2);lcd.print(" ");k--;}}
  
  k=0;
  while (k<m){k++; if (confirmpw[k] != password[k]){flag=false;}}
  
  if (flag == false){
    delay(200);
    lcd.clear();
    lcd.setCursor(0,0);lcd.print("Wrong confirmation...");
    lcd.setCursor(0,1);lcd.print("Reseting Again...");
    delay(200);
    setpw();}
}

void checkpw(){
  delay(200);
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Enter Password...");
  lcd.setCursor(0,1);lcd.print("3 trials ,confirm #");
  lcd.setCursor(0,3);lcd.print("          delete  *");
  k=0;
  flag=true;
  while (k<pwlength){
  key = keypad.getKey();
  if (key && key!='*' && key!='#'){
  k++;
  password[k]= key;
  lcd.setCursor(k,2);lcd.print(password[k]);}
  if (key == '#' && k>2){if (m != k){flag=false;}k=pwlength;}
  else if (key == '*' && k>0){lcd.setCursor(k,2);lcd.print(" ");k--;}}
  k=0;
  while (k<m){k++;if (password[k] != confirmpw[k]){flag=false;}}
  checkflag();
  }

void checkflag(){
  if(!flag){
  j++;
  delay(200);
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Wrong Password...");
  lcd.setCursor(0,1);lcd.print("trial ");
  lcd.setCursor(6,1);lcd.print(j);
  lcd.setCursor(7,1);lcd.print(" failed");
  delay(200);
  lcd.clear();
  if(j>2){theifmode();}
  checkpw();
  lcd.clear();
  fire();}
}

void theifmode(){
  lcd.clear();
  fire();
  digitalWrite(theif,HIGH);
  lcd.setCursor(0,0);lcd.print("3 Times Wrong...");
  lcd.setCursor(0,1);lcd.print("Theif mode door locked");
  lcd.setCursor(0,2);lcd.print("Calling owner...");
  lcd.setCursor(5,3);lcd.print("SEE you 4715");
  delay(3000);
  j=0;
  digitalWrite(theif,LOW);
  checkpw();
  }
