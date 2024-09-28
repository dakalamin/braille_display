#pragma once

#include "config.h"


enum NcharSpecial : nchar32_t {
	LF = 10,

	INVALID_NCHAR = UINT8_MAX,
	EMPTY_NCHAR   = INVALID_NCHAR - 1,
};

nchar32_t readUTF8Char() {
	nchar32_t input = Serial.read();
	byte octetsToRead;

	if (input >> 7 == 0b0)
		return input;       // 0xxxxxxx -> 1 octet
	else if (input >> 5 == 0b110)
		octetsToRead = 1;   // 110xxxxx -> 2 octets (1 octet to read)
	else if (input >> 4 == 0b1110)
		octetsToRead = 2;   // 1110xxxx -> 3 octets (2 octets to read)
	else if (input >> 3 == 0b11110)
		octetsToRead = 3;   // 11110xxx -> 4 octets (3 octets to read)
	else
		return INVALID_NCHAR;  // anything else -> invalid

	delay(MIN_DELAY_MS);  // Necessary between Serial.read() and Serial.available()
	if (Serial.available() < octetsToRead)
		return INVALID_NCHAR;

	for (; octetsToRead > 0; octetsToRead--) {
		nchar32_t octet = Serial.read();
		if (octet >> 6 != 0b10)
			return INVALID_NCHAR;  // not 10xxxxxx -> invalid

		input = input << 8 | octet;
	}
	return input;
}

nchar32_t reservedNchar = EMPTY_NCHAR;
bool getNextNchar(nchar32_t& nchar) {
	if (reservedNchar != EMPTY_NCHAR) {
		nchar         = reservedNchar;
		reservedNchar = EMPTY_NCHAR;
		return true;
	}

	if (!Serial.available())
		return false;

	nchar = readUTF8Char();
	return true;
}