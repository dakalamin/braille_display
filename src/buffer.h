#pragma once

#include "config.h"
#include "patterns.h"


const byte BUFFER_SIZE = BRAILLE_CELLS + 1;
byte buffer[BUFFER_SIZE];

/*
	Shift buffer left and return index of the first empty element after the shift
	
	After elements are sent to display, first BRAILLE_CELLS elements are cleared,
	but some non-empty elements may remain in the buffer

	e.g.: let BRAILLE_CELLS = 4 and BUFFER_SIZE = 7
	-----------------------------  0   1   2   3   4   5   6  
	initial state: ------------- | A | B | C | D | E | F | . |
	after showBuffer(): -------- | . | . | . | . | E | F | . | ( ABCD on display )
	after shiftBufferLeft(): --- | E | F |[.]| . | . | . | . |

	[.] is the first empty element, its index is returned -> 2
*/
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

void clearBuffer(byte indexFrom, byte indexTo) {
	for (byte i = indexFrom; i < indexTo; i++)
		buffer[i] = EMPTY;
}
void clearBuffer(byte indexTo=BUFFER_SIZE) {
	clearBuffer(0, indexTo);
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
