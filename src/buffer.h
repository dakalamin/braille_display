#pragma once

#include "nchar.h"
#include "config.h"
#include "patterns.h"


class Buffer {
public:
	static Buffer& getInstance() {
		static Buffer INSTANCE;
		return INSTANCE;
	}

private:
	Buffer() { }

public:
	void initialize() {
		Buffer::size = brailleCells + 1;
		_contents = new byte[size];

		clear();
	}

	/*
		Shift buffer left and return index of the first empty element after the shift
		
		After elements are sent to display, first BRAILLE_CELLS elements are cleared,
		but some non-empty elements may remain in the buffer

		e.g.: let brailleCells = 4 and Buffer::size = 7
		-----------------------------  0   1   2   3   4   5   6  
		initial state: ------------- | A | B | C | D | E | F | . |
		after showBuffer(): -------- | . | . | . | . | E | F | . | ( ABCD on display )
		after shiftBufferLeft(): --- | E | F |[.]| . | . | . | . |

		[.] is the first empty element, its index is returned -> 2
	*/
	byte shiftLeft() {
		byte to = 0;
		for (byte from = brailleCells; from < size; from++, to++) {
			byte element = _contents[from];
			if (element == EMPTY)
				break;

			_contents[to]   = element;
			_contents[from] = EMPTY;
		}
		return to;
	}

	void clear(byte indexFrom=0, byte indexTo=size) {
		for (byte i = indexFrom; i < indexTo; i++)
			_contents[i] = EMPTY;
	}

	void add(byte element);  // defined in translation.h
	void add(byte element, byte& index) {
		_contents[index++] = element;
	}

	void addAndEcho(byte element, nchar32_t nchar) {
		add(element);

		#if SERIAL_ECHO
			printNchar(nchar);
		#endif
	}

	void show() {
		digitalWrite(LATCH_PIN, LOW);

		for (byte i = brailleCells; i > 0; i--)
			shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, _contents[i - 1]);

		digitalWrite(LATCH_PIN, HIGH);
	}

private:
	byte* _contents;
public:
	static byte size;
};

byte Buffer::size;
Buffer& buffer = Buffer::getInstance();
