/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

const int SWITCH_A = 28;
const int SWITCH_B = 30;
const int SWITCH_C = 32;
const int SWITCH_D = 29;
const int SWITCH_E = A14;
const int SWITCH_F = A15;
const int LED_A = 22;
const int LED_B = 24;
const int LED_C = 26;
const int LED_D = 23;
const int LED_E = 25;
const int LED_F = 27;

int stateA = 0;
int stateB = 0;
int stateC = 0;
int stateD = 0;
int stateE = 0;
int stateF = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(SWITCH_A, INPUT);
  pinMode(SWITCH_B, INPUT);
  pinMode(SWITCH_C, INPUT);
  pinMode(SWITCH_D, INPUT);
  //pinMode(SWITCH_E, INPUT);
  //pinMode(SWITCH_F, INPUT);
        
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value:
  stateA = digitalRead(SWITCH_A);
  stateB = digitalRead(SWITCH_B);
  stateC = digitalRead(SWITCH_C);
  stateD = digitalRead(SWITCH_D);
  stateE = analogRead(SWITCH_E);
  stateF = analogRead(SWITCH_F);
  
  Serial.print(stateA);
  Serial.print(", ");
  Serial.print(stateB);
  Serial.print(", ");
  Serial.print(stateC);
  Serial.print(", ");
  Serial.print(stateD);
  Serial.print(", ");
  Serial.print(stateE);
  Serial.print(", ");
  Serial.print(stateF);
  Serial.println();
  
  if (stateA == LOW) {
    digitalWrite(LED_A, HIGH);
  } else {
    digitalWrite(LED_A, LOW);
  }

  if (stateB == LOW) {
    digitalWrite(LED_B, HIGH);   
  } else {
    digitalWrite(LED_B, LOW);   
  }

  if (stateC == LOW) {
    digitalWrite(LED_C, HIGH);  
  } else {
    digitalWrite(LED_C, LOW);   
  }  

  if (stateD == LOW) {
    digitalWrite(LED_D, HIGH);  
  } else {
    digitalWrite(LED_D, LOW);   
  }  

  if (stateE < 5) {
    digitalWrite(LED_E, HIGH);  
  } else {
    digitalWrite(LED_E, LOW);   
  }  

  if (stateF < 5) {
    digitalWrite(LED_F, HIGH);  
  } else {
    digitalWrite(LED_F, LOW);   
  }  

  delay(1);
}