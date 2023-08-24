/* this project targets lead train application 
for three leds in one directions (forward)*/

int redled = 9;
int greenled = 10;
int yellowled = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(yellowled,OUTPUT);
}

void loop() {
// put your main code here, to run repeatedly:
// forward direction control of leds
       digitalWrite(redled,HIGH);
       digitalWrite(greenled,LOW);
       digitalWrite(yellowled,LOW);
       delay(500);
       digitalWrite(redled,LOW);
       digitalWrite(greenled,HIGH);
       digitalWrite(yellowled,LOW);
       delay(500);
       digitalWrite(redled,LOW);
       digitalWrite(greenled,LOW);
       digitalWrite(yellowled,HIGH);
       delay(500);
}
