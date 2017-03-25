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

bool playing = false;
int currentNote = 0;
unsigned long currentNoteStart = 0;

void loop() {

   readInputs();

   Serial.print(swch[0]); Serial.print(", ");
   Serial.print(swch[1]); Serial.print(", ");
   Serial.print(swch[2]); Serial.print(", ");
   Serial.print(bttn[0]); Serial.print(", ");
   Serial.print(bttn[1]); Serial.print(", ");
   Serial.print(bttn[2]); Serial.println();
   Serial.print(playing); Serial.print(", ");
   Serial.print(currentNote); Serial.print(", ");
   Serial.print(currentNoteStart); Serial.print(", ");

   if (playing) {
      play();
   }

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
      if (bttn[1] && !playing) {
         playing = true;
      }
   }
   // test column leds
   for (int i = 0; i < 5; i++) {
      digitalWrite(LED_BLU[i], bttn[0] ? HIGH : LOW);
      digitalWrite(LED_YEL[i], bttn[1] ? HIGH : LOW);
      digitalWrite(LED_RED[i], bttn[2] ? HIGH : LOW);
   }
}

void play() {
   unsigned long currentMillis = millis();
   // First time though - Start us off
   if (currentNote == 0 && currentNoteStart == 0) {
      currentNoteStart = currentMillis;
      tone(SPEAKER, melody[currentNote], 100);
   } else if (currentNote > 8) {
      // We're done!
      playing = false;
      currentNote = 0;
      currentNoteStart = 0;
   } else {
      unsigned long desiredNoteDuration = 1000 / noteDurations[currentNote];
      unsigned long totalDesiredDuration = desiredNoteDuration * 1.30;
      unsigned long currentProgress = currentMillis - currentNoteStart;

      if (currentProgress < desiredNoteDuration) {
         // Not done yet, keep playing...
         tone(SPEAKER, melody[currentNote], 100);
      } else if (currentProgress > desiredNoteDuration && currentProgress < totalDesiredDuration) {
         // Done with note, pause...
         noTone(SPEAKER);
      } else {
         currentNote++;
         currentNoteStart = currentMillis;
      }
   }
}
