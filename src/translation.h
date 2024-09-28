#pragma once

#include "buffer.h"
#include "config.h"
#include "patterns.h"
#include "nchar.h"


enum NcharAttribute : byte {
	COMMON        = 1 << 0,
	IS_RUSSIAN    = 1 << 1,
	IS_UPPER_CASE = 1 << 2,
	IS_NUMERIC    = 1 << 3,
};

enum MessageAttribute : byte {
	NEW_MESSAGE       = 0,
	QUOTATION_PARITY  = 1 << 0,
	NUMERIC_MOD_ACTIVE = 1 << 1,
};
byte messageAttributes = NEW_MESSAGE;

byte firstEmptyIndex = 0;


void addToBuffer(byte element) {
	addToBuffer(element, firstEmptyIndex);
}


byte ncharToBraille(nchar32_t nchar, byte& attribute) {
	attribute = COMMON;

	byte index;
	const braille_t* array;

	if (nchar < PUNCT1_CHAR)  // ----------------------------------- BEFORE PUNCTUATION
		return NA;
	else if (nchar < '0') {  // ------------------------------------ PUNCTUATION FROM ' ' to '/'
		index = nchar - PUNCT1_CHAR;                              // (ASCII FROM 32 TO 47)
		array = PUNCT1_TO_BRAILLE;
	}
	else if (nchar < PUNCT2_CHAR) {  // ---------------------------- NUMERIC
		attribute = IS_NUMERIC;
		index = (nchar == '0') ? 9 : (nchar - 1 - '0');
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if (nchar < 'A') {  // ------------------------------------ PUNCTUATION FROM ':' to '@'
		index = nchar - PUNCT2_CHAR;                              // (ASCII FROM 58 TO 64)
		array = PUNCT2_TO_BRAILLE;
	}
	else if (nchar <= 'Z') {  // ----------------------------------- ENGLISH UPPER CASE
		attribute = IS_UPPER_CASE;
		index = nchar - 'A';
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if ('a' <= nchar && nchar <= 'z') {  // ------------------- ENGLISH LOWER CASE
		index = nchar - 'a';
		array = ENG_NUMERIC_TO_BRAILLE;
	}
	else if ((uint16_t)'А' <= nchar && nchar <= (uint16_t)'Я') {  // RUSSIAN UPPER CASE
		attribute = IS_RUSSIAN | IS_UPPER_CASE;
		index = nchar - (uint16_t)'А';
		array = RUSSIAN_TO_BRAILLE;
	}
	else if ((uint16_t)'а' <= nchar && nchar <= (uint16_t)'я') {  // RUSSIAN LOWER CASE
		attribute = IS_RUSSIAN;
		index = nchar - (uint16_t)'а';
		array = RUSSIAN_TO_BRAILLE;
	}
	else if (nchar == (uint16_t)'Ё') {  // ------------------------- RUSSIAN Ё
		attribute = IS_RUSSIAN | IS_UPPER_CASE;
		index = 32;
		array = RUSSIAN_TO_BRAILLE;
	}
	else if (nchar == (uint16_t)'ё') {  // ------------------------- RUSSIAN ё
		attribute = IS_RUSSIAN;
		index = 32;
		array = RUSSIAN_TO_BRAILLE;
	}
	else
		return NA;  // --------------------------------------------- ANYTHING ELSE

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
		addToBuffer(ncharToBraille('"'));

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

	addToBuffer(DECIMAL_POINT);
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
			addToBuffer(NUMERIC_MOD);
		}
		addToBuffer(braille);
		return true;
	}
	messageAttributes &= ~NUMERIC_MOD_ACTIVE;

	if (nchar == '"') {
		if (messageAttributes & QUOTATION_PARITY)
			braille = flipV(braille);
	
		messageAttributes ^= QUOTATION_PARITY;
	}
	else if (nchar == '*')
		addToBuffer(braille);
	else if (ncharAttributes & IS_UPPER_CASE)
		addToBuffer(CAPITAL_MOD);

	addToBuffer(braille);
	return true;
}


bool prepareToShow() {
	bool messageInputRemains = true;
	firstEmptyIndex = shiftBufferLeft();

	while (firstEmptyIndex < BRAILLE_CELLS && messageInputRemains)
		messageInputRemains = readAndProcess();

	if (firstEmptyIndex == 0)
		return false;

	clearBuffer(firstEmptyIndex, BUFFER_SIZE);
    return true;
}