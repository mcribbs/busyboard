#ifndef BUSYBOARD_H_
#define BUSYBOARD_H_

#include "pitches.h"

// Define input pins
const int SWITCH[] = {13, 12, 11};
const int BUTTON[] = {A8, A9, 10};
const int BUTTON_ANALOG[] = {true, true, false};

// Define output pins
const int LED_RED[] = {22, 23, 24, 25, 26};
const int LED_YEL[] = {27, 28, 29, 30, 31};
const int LED_BLU[] = {32, 33, 34, 35, 36};
const int LED_SAG[] = {39, 40, 41, 38, 37, 44, 45, 46, 47, 48, 49, 50, 42, 43};
const int SPEAKER = 8;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

#endif // BUSYBOARD_H_
