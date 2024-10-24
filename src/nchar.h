#pragma once

#include "config.h"


enum NcharSpecial : nchar32_t {
	LF = 10,

	INVALID_NCHAR = UINT8_MAX,
	EMPTY_NCHAR   = INVALID_NCHAR - 1,
};
enum NcharAttribute : byte {
	COMMON        = 1 << 0,
	IS_RUSSIAN    = 1 << 1,
	IS_UPPER_CASE = 1 << 2,
	IS_NUMERIC    = 1 << 3,
};

nchar32_t readUTF8Char() {
	nchar32_t input = Serial.read();
	byte octetsToRead;

	if (input >> 7 == 0b0)
		return input;       // 0xxxxxxx -> symbol is already read
	else if (input >> 5 == 0b110)
		octetsToRead = 1;   // 110xxxxx -> 1 octet to read  (2 octets total)
	else if (input >> 4 == 0b1110)
		octetsToRead = 2;   // 1110xxxx -> 2 octets to read (3 octets total)
	else if (input >> 3 == 0b11110)
		octetsToRead = 3;   // 11110xxx -> 3 octets to read (4 octets total)
	else
		return INVALID_NCHAR;  // anything else -> invalid

	delay(MIN_DELAY_MS);  // Serial.available() needs a small delay between calls and after Serial.read()
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

void printNchar(nchar32_t nchar) {
	if (nchar == INVALID_NCHAR)
		return printNchar(0xEFBFBD);  // � (U+FFFD)

	byte ncharBytes = 1;
	for (; (nchar >> (8 * ncharBytes)) & UINT8_MAX; ncharBytes++) { }

	char* output = new char[ncharBytes + 1];
	output[ncharBytes] = 0;  // last byte must be 0
	for (; ncharBytes > 0; ncharBytes--, nchar >>= 8)
		output[ncharBytes - 1] = nchar & UINT8_MAX;
		
	Serial.print(output);
	delete [] output;
}
