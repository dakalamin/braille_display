#pragma once

#include "config.h"
#include "patterns.h"


const byte BUFFER_SIZE = BRAILLE_CELLS + 1;
byte buffer[BUFFER_SIZE];

byte shiftBufferLeft() {
	byte to = 0;
	for (byte from = BRAILLE_CELLS; from < BUFFER_SIZE; from++, to++) {
		byte element = buffer[from];
		if (element == EMPTY)
			break;

		buffer[to]   = element;
		buffer[from] = EMPTY;
	}
	return to;
}

void clearBuffer() {
	for (byte i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = EMPTY;
}

void addToBuffer(byte element, byte& index) {
	buffer[index++] = element;
}

void showBuffer() {
    digitalWrite(latchPin, LOW);

	for (byte i = BRAILLE_CELLS; i > 0; i--)
		shiftOut(dataPin, clockPin, MSBFIRST, buffer[i - 1]);

	digitalWrite(latchPin, HIGH);
}
