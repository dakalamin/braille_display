#pragma once

#include "buffer.h"
#include "config.h"
#include "patterns.h"
#include "nchar.h"


enum MessageAttribute : byte {
	NEW_MESSAGE        = 0,
	QUOTATION_PARITY   = 1 << 0,
	NUMERIC_MOD_ACTIVE = 1 << 1,
};
byte messageAttributes = NEW_MESSAGE;

const byte RUS_ALPHABET_LEN = 32;  // without 'Ё'
enum RussianChar16 : uint16_t {
	RUS_UPPER_FIRST = 0xD090,  // А
	RUS_UPPER_LAST  = 0xD0AF,  // Я
	RUS_UPPER_YO    = 0xD081,  // Ё

	RUS_LOWER_FIRST = 0xD0B0,  // а
	RUS_LOWER_LAST  = 0xD18F,  // я
	RUS_LOWER_YO    = 0xD191,  // ё
};

byte firstEmptyIndex = 0;


void Buffer::add(byte element) {
	add(element, firstEmptyIndex);
}


byte ncharToBraille(nchar32_t nchar, byte& attribute) {
	attribute = COMMON;

	byte index;
	const braille_t* array;

	if (nchar < PUNCT1_CHAR)  // -------------------------------------- BEFORE PUNCTUATION
		return NA;
	else if (nchar < '0') {  // --------------------------------------- PUNCTUATION FROM ' ' to '/'
		index = nchar - PUNCT1_CHAR;                                 // (ASCII FROM 32 TO 47)
		array = PUNCT1_TO_BRAILLE;
	}
	else if (nchar < PUNCT2_CHAR) {  // ------------------------------- NUMERIC
		attribute = IS_NUMERIC;
		index = (nchar == '0') ? 9 : (nchar - 1 - '0');
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if (nchar < 'A') {  // --------------------------------------- PUNCTUATION FROM ':' to '@'
		index = nchar - PUNCT2_CHAR;                                 // (ASCII FROM 58 TO 64)
		array = PUNCT2_TO_BRAILLE;
	}
	else if (nchar <= 'Z') {  // -------------------------------------- ENGLISH UPPER CASE
		attribute = IS_UPPER_CASE;
		index = nchar - 'A';
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if ('a' <= nchar && nchar <= 'z') {  // ---------------------- ENGLISH LOWER CASE
		index = nchar - 'a';
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if (RUS_UPPER_FIRST <= nchar && nchar <= RUS_UPPER_LAST) {  // RUSSIAN UPPER CASE
		attribute = IS_RUSSIAN | IS_UPPER_CASE;
		index = nchar - RUS_UPPER_FIRST;
		array = RUSSIAN_TO_BRAILLE;
	}
	else if (RUS_LOWER_FIRST <= nchar && nchar <= RUS_LOWER_LAST) {  // RUSSIAN LOWER CASE
		attribute = IS_RUSSIAN;
		index = nchar - RUS_LOWER_FIRST;
		// from 'р' to 'я' values are shifted by +192
		// ...
		// 'о' = [110]10000 [10]111110 -> 'о' - 'а' = 14
		// 'п' = [110]10000 [10]111111 -> 'п' - 'а' = 15
		// 'р' = [110]10001 [10]000000 -> 'р' - 'а' = 208 -> 208 - 192 = 16
		// 'с' = [110]10001 [10]000001 -> 'с' - 'а' = 209 -> 208 - 192 = 17
		// ...
		if (index > RUS_ALPHABET_LEN)
			index -= 192;
		array = RUSSIAN_TO_BRAILLE;
	}
	else if (nchar == RUS_UPPER_YO) {  // ----------------------------- RUSSIAN Ё
		attribute = IS_RUSSIAN | IS_UPPER_CASE;
		index = RUS_ALPHABET_LEN;
		array = RUSSIAN_TO_BRAILLE;
	}
	else if (nchar == RUS_LOWER_YO) {  // ----------------------------- RUSSIAN ё
		attribute = IS_RUSSIAN;
		index = RUS_ALPHABET_LEN;
		array = RUSSIAN_TO_BRAILLE;
	}
	else
		return NA;  // ------------------------------------------------ ANYTHING ELSE

	return pgm_read_byte(&array[index]);
}

byte ncharToBraille(nchar32_t nchar) {
	byte dummyAttribute;
	return ncharToBraille(nchar, dummyAttribute);
}

void eomRoutine(bool eomCondition=true) {
	if (!eomCondition)
		return;

	if (messageAttributes & QUOTATION_PARITY)
		buffer.add(ncharToBraille('"'));

	messageAttributes = NEW_MESSAGE;
}

bool processDotSpecialCase() {
	const nchar32_t NCHAR_DOT = '.';

	nchar32_t nextNchar;
	if (!getNextNchar(nextNchar)) {
		eomRoutine(SERIAL_NA_IS_EOM);
		reservedNchar = NCHAR_DOT;
		return false;
	}
	if (nextNchar == LF) {
		eomRoutine(LF_IS_EOM);
		reservedNchar = NCHAR_DOT;
		return true;
	}

	reservedNchar = nextNchar;

	byte nextNcharAttributes;
	ncharToBraille(nextNchar, nextNcharAttributes);
	if (~nextNcharAttributes & IS_NUMERIC)
		return false;

	buffer.addAndEcho(DECIMAL_POINT, NCHAR_DOT);
	return true;
}

bool readAndProcess() {
	nchar32_t nchar;
	if (!getNextNchar(nchar)) {
		eomRoutine(SERIAL_NA_IS_EOM);
		return false;
	}
	if (nchar == LF) {
		eomRoutine(LF_IS_EOM);
		return !LF_IS_EOM;
	}

	if (nchar == '.' && messageAttributes & NUMERIC_MOD_ACTIVE)
		return processDotSpecialCase();

	byte ncharAttributes;
	braille_t braille = ncharToBraille(nchar, ncharAttributes);

	if (ncharAttributes & IS_NUMERIC) {
		if (~messageAttributes & NUMERIC_MOD_ACTIVE) {
			messageAttributes |= NUMERIC_MOD_ACTIVE;
			buffer.add(NUMERIC_MOD);
		}
		buffer.addAndEcho(braille, nchar);
		return true;
	}
	messageAttributes &= ~NUMERIC_MOD_ACTIVE;

	if (nchar == '"') {
		if (messageAttributes & QUOTATION_PARITY)
			braille = flipV(braille);
	
		messageAttributes ^= QUOTATION_PARITY;
	}
	else if (nchar == '*')
		buffer.add(braille);
	else if (ncharAttributes & IS_UPPER_CASE)
		buffer.add(CAPITAL_MOD);

	buffer.addAndEcho(braille, nchar);
	return true;
}


bool readyToShow() {
	bool messageInputRemains = true;
	firstEmptyIndex = buffer.shiftLeft();

	while (firstEmptyIndex < brailleCells && messageInputRemains)
		messageInputRemains = readAndProcess();

	if (firstEmptyIndex == 0)
		return false;

	#if SERIAL_ECHO
		Serial.println();
	#endif

	buffer.clear(firstEmptyIndex);
    return true;
}
