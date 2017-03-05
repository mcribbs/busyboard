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

}

// Input state trackers
int swch[] = {0, 0, 0};
int bttn[] = {0, 0, 0};

bool testMode = false;

void loop() {

   readInputs();

   Serial.print(swch[0]); Serial.print(", ");
   Serial.print(swch[1]); Serial.print(", ");
   Serial.print(swch[2]); Serial.print(", ");
   Serial.print(bttn[0]); Serial.print(", ");
   Serial.print(bttn[1]); Serial.print(", ");
   Serial.print(bttn[2]); Serial.println();

   if (testMode) {
      doTests();
      return;
   }

   if (!swch[2]) {
      // "off mode", just listen for test mode trigger
      if (bttn[0] && bttn[1] && bttn[2]) {
         testMode = true;
      }
   } else {
      // do all the active things
   }

   delay(1);
}

void readInputs() {
   // Read inputs (wired to normally high to reverse for "normal" logic)
   for (int i = 0; i < 3; i++) {
      swch[i] = !digitalRead(SWITCH[i]);
      if (!BUTTON_ANALOG[i]) {
         bttn[i] = !digitalRead(BUTTON[i]);
      } else {
         bttn[i] = analogRead(BUTTON[i]) < 5 ? HIGH : LOW;
      }
   }
}

void doTests() {
   if (swch[2]) {
      // Exit test mode
      testMode = false;
      for (int i = 0; i < 5; i++) {
         digitalWrite(LED_BLU[i], LOW);
         digitalWrite(LED_YEL[i], LOW);
         digitalWrite(LED_RED[i], LOW);
      }
      for (int i = 0; i < 14; i++) {
         digitalWrite(LED_SAG[i], LOW);
      }
      return;
   }
   if (swch[0]) {
      // test sag leds
      for (int i = 0; i < 14; i++) {
         digitalWrite(LED_SAG[i], HIGH);
      }
   } else {
      for (int i = 0; i < 14; i++) {
         digitalWrite(LED_SAG[i], LOW);
      }
   }
   if (swch[1]) {
      // test sound
      if (bttn[1]) {
         // iterate over the notes of the melody:
         for (int thisNote = 0; thisNote < 8; thisNote++) {

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
   } else {
      // test column leds
      for (int i = 0; i < 5; i++) {
         digitalWrite(LED_BLU[i], bttn[0] ? HIGH : LOW);
         digitalWrite(LED_YEL[i], bttn[1] ? HIGH : LOW);
         digitalWrite(LED_RED[i], bttn[2] ? HIGH : LOW);
      }
   }
}
