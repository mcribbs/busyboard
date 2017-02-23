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

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


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

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
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
