#pragma once

#include "config.h"


enum BrailleSpecial : braille_t {
	NA    = 0b111111,          // ⠿
	EMPTY = 1 << 6,            // ⠀ (not equal to 0)

	DECADE_2 = 0b000100,       // ⠄
	DECADE_3 = 0b100100,       // ⠤
	DECADE_4 = 0b100000,       // ⠠

	CAPITAL_MOD = 0b100000,    // ⠠
	NUMERIC_MOD = 0b111100,    // ⠼

	DECIMAL_POINT = 0b101000,  // ⠨
};


// Braille pattern vertical flip (⠧ ⟶ ⠼)
constexpr braille_t flipV(braille_t pattern) {
	return ((pattern & 0b100100) >> 2) | (pattern & 0b010010) | ((pattern & 0b001001) << 2);
}

// Braille pattern horizontal flip (⠧ ⟶ ⠏)
constexpr braille_t flipH(braille_t pattern) {
	return ((pattern & 0b000111) << 3) | ((pattern & 0b111000) >> 3);
}


const char PUNCT1_CHAR = ' ';
const PROGMEM braille_t PUNCT1_TO_BRAILLE[] = {
	0b000000,     // ⠀ SPACE
	0b010110,     // ⠖ !
	0b100110,     // ⠦ " - flipped vertically on close ⟶ ⠴
	NUMERIC_MOD,  // ⠼ #
	NA,           // ⠿ $
	NA,           // ⠿ %
	0b101111,     // ⠯ &
	0b000100,     // ⠄ '
	0b110110,     // ⠶ (
	0b110110,     // ⠶ )
	0b010100,     // ⠔ * - doubled ⟶ ⠔⠔
	NA,           // ⠿ +
	0b000010,     // ⠂ ,
	0b100100,     // ⠤ -
	0b110010,     // ⠲ .
	0b001100,     // ⠌ /
};
const char PUNCT2_CHAR = ':';
const PROGMEM braille_t PUNCT2_TO_BRAILLE[] = {
	0b010010,  // ⠒ :
	0b000110,  // ⠆ ;
	NA,        // ⠿ <
	NA,        // ⠿ =
	NA,        // ⠿ >
	0b100110,  // ⠦ ?
	NA,        // ⠿ @
};

const PROGMEM braille_t ENG_NUMERIC_TO_BRAILLE[] = {
	0b000001,             // ⠁ A/1
	0b000011,             // ⠃ B/2
	0b001001,             // ⠉ C/3
	0b011001,             // ⠙ D/4
	0b010001,             // ⠑ E/5
	0b001011,             // ⠋ F/6
	0b011011,             // ⠛ G/7
	0b010011,             // ⠓ H/8
	0b001010,             // ⠊ I/9
	0b011010,             // ⠚ J/0
	0b000001 + DECADE_2,  // ⠅ K - A2
	0b000011 + DECADE_2,  // ⠇ L - B2
	0b001001 + DECADE_2,  // ⠍ M - C2
	0b011001 + DECADE_2,  // ⠝ N - D2
	0b010001 + DECADE_2,  // ⠕ O - E2
	0b001011 + DECADE_2,  // ⠏ P - F2
	0b011011 + DECADE_2,  // ⠟ Q - G2
	0b010011 + DECADE_2,  // ⠗ R - H2
	0b001010 + DECADE_2,  // ⠎ S - I2
	0b011010 + DECADE_2,  // ⠞ T - J2
	0b000001 + DECADE_3,  // ⠥ U - A3
	0b000011 + DECADE_3,  // ⠧ V - B3
	0b011010 + DECADE_4,  // ⠺ W - J4
	0b001001 + DECADE_3,  // ⠭ X - C3
	0b011001 + DECADE_3,  // ⠽ Y - D3
	0b010001 + DECADE_3,  // ⠵ Z - E3
};

const PROGMEM braille_t RUSSIAN_TO_BRAILLE[] = {
	0b000001,  // ⠁ А
	0b000011,  // ⠃ Б
	0b111010,  // ⠺ В
	0b011011,  // ⠛ Г
	0b011001,  // ⠙ Д
	0b010001,  // ⠑ Е
	0b011010,  // ⠚ Ж
	0b110101,  // ⠵ З
	0b001010,  // ⠊ И
	0b101111,  // ⠯ Й
	0b000101,  // ⠅ К
	0b000111,  // ⠇ Л
	0b001101,  // ⠍ М
	0b011101,  // ⠝ Н
	0b010101,  // ⠕ О
	0b001111,  // ⠏ П
	0b010111,  // ⠗ Р
	0b001110,  // ⠎ С
	0b011110,  // ⠞ Т
	0b100101,  // ⠥ У
	0b001011,  // ⠋ Ф
	0b010011,  // ⠓ Х
	0b001001,  // ⠉ Ц
	0b011111,  // ⠟ Ч
	0b110001,  // ⠱ Ш
	0b101101,  // ⠭ Щ
	0b110111,  // ⠷ Ъ
	0b101110,  // ⠮ Ы
	0b111110,  // ⠾ Ь
	0b101010,  // ⠪ Э
	0b110011,  // ⠳ Ю
	0b101011,  // ⠫ Я

	0b100001,  // ⠡ Ё	
};