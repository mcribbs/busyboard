#include "busyboard.h"
#include "pitches.h"

void setup() {
  Serial.begin(9600);

  // Setup inputs
  for (int i = 0; i < 3; i++) {
    pinMode(SWITCH[i], INPUT);
    if (!BUTTON_ANALOG[i]) {
       pinMode(BUTTON[i], INPUT);
    }
  }

  // Setup outputs
  for (int i = 0; i < 5; i++) {
    pinMode(LED_RED[i], OUTPUT);
    pinMode(LED_YEL[i], OUTPUT);
    pinMode(LED_BLU[i], OUTPUT);
  }
  for (int i = 0; i < 14; i++) {
    pinMode(LED_SAG[i], OUTPUT);
  }

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < SPEAKER; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    switch_state[i] = digitalRead(SWITCH[i]);
    if (!BUTTON_ANALOG[i]) {
       button_state[i] = digitalRead(BUTTON[i]);
    } else {
      button_state[i] = analogRead(BUTTON[i]) < 5 ? LOW : HIGH;
    }
  }

  /*
  Serial.print(switch_state[0]); Serial.print(", ");
  Serial.print(switch_state[1]); Serial.print(", ");
  Serial.print(switch_state[2]); Serial.print(", ");
  Serial.print(button_state[0]); Serial.print(", ");
  Serial.print(button_state[1]); Serial.print(", ");
  Serial.print(button_state[2]); Serial.println();
  */

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BLU[i], !switch_state[0] ? HIGH : LOW);
    digitalWrite(LED_YEL[i], !switch_state[1] ? HIGH : LOW);
    digitalWrite(LED_RED[i], !switch_state[2] ? HIGH : LOW);
  }
  for (int i = 0; i < 14; i++) {
    digitalWrite(LED_SAG[i], !button_state[0] ? HIGH : LOW);
  }

  delay(1);
}
