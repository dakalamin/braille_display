#pragma once

#include "config.h"
#include "patterns.h"


void _shiftOut(byte pattern) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, pattern);
    digitalWrite(latchPin, HIGH);
}

void countBrailleCells() {
    #if AUTOCOUNT_CELLS
        _shiftOut(AUTOCOUNT_BIT | ((ANIMATION_ON_START) ? NA : EMPTY));

        for (brailleCells = 0; digitalRead(autoPin); brailleCells++) {
            delay((ANIMATION_ON_START) ? ANIMATION_MS_PER_CELL : MIN_DELAY_MS);
            _shiftOut(0);
        }
    #else
        brailleCells = BRAILLE_CELLS;

        #if ANIMATION_ON_START
            for (byte i = 0; i < brailleCells; i++) {
                delay(ANIMATION_MS_PER_CELL);
                _shiftOut(0);
            }
        #endif
    #endif
}
