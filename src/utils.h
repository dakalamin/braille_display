#pragma once

#include "config.h"
#include "patterns.h"


void _shiftOut(byte pattern=0) {
	digitalWrite(LATCH_PIN, LOW);
	shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pattern);
	digitalWrite(LATCH_PIN, HIGH);
}

void countBrailleCells() {
	#if AUTOCOUNT_CELLS
		_shiftOut(AUTOCOUNT_BIT | ((ANIMATION_ON_START) ? NA : EMPTY));

		for (brailleCells = 0; digitalRead(AUTO_PIN); brailleCells++) {
			delay((ANIMATION_ON_START) ? ANIMATION_MS_PER_CELL : MIN_DELAY_MS);
			_shiftOut();
		}
	#else
		brailleCells = BRAILLE_CELLS;

		#if ANIMATION_ON_START
			for (byte i = 0; i < brailleCells; i++) {
				delay(ANIMATION_MS_PER_CELL);
				_shiftOut();
			}
		#endif
	#endif
}
