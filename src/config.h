#pragma once

#include <Arduino.h>


/*
	Normalized UTF-8 char (nUTF-8) - left padded with 0s to reach 32 bits
	e.g.: "⠳" (U+2833) - E2 A0 B3 (hex UTF-8) - 00 E2 A0 B3 (hex nUTF-8)
*/
typedef uint32_t nchar32_t;

/*
	Braille 6-dot pattern:
	(1)(4)
	(2)(5) ⟶ 0bXX(6)(5)(4)(3)(2)(1)
	(3)(6)
	'X's are 'whatever' bits, additional information can be coded here

	e.g.: "⠫" ⟶ (1)(2)(4)(6) ⟶ 0b101011
*/
typedef uint8_t braille_t;


#define AUTO_PIN   7
#define BUTTON_PIN 8
#define DATA_PIN   11  //    DS pin of 74HC595 shift register
#define LATCH_PIN  12  // ST_CP pin of 74HC595 shift register
#define CLOCK_PIN  13  // SH_CP pin of 74HC595 shift register


#ifndef PLATFORMIO
	#include "custom_config.h"
#endif


#ifndef BAUD_RATE
	#define BAUD_RATE 9600
#endif

#define MIN_DELAY_MS 2

#ifndef BUTTON_CLICK_MS
	#define BUTTON_CLICK_MS 100
#endif
#ifndef BUTTON_CYCLE_MS
	#define BUTTON_CYCLE_MS 1000
#endif


#define AUTOCOUNT_BIT (1 << 7)
#ifndef AUTOCOUNT_CELLS
	#define AUTOCOUNT_CELLS true
#endif
#ifndef BRAILLE_CELLS
	#define BRAILLE_CELLS 4
#endif

#ifndef ANIMATION_ON_START
	#define ANIMATION_ON_START true
#endif
#ifndef ANIMATION_MS_PER_CELL
	#define ANIMATION_MS_PER_CELL 500
#endif

#ifndef SERIAL_ECHO
	#define SERIAL_ECHO true
#endif

#ifndef LF_IS_EOM
	/*
		LF is End Of Message
		If 0, concatinates messages before and after LF symbol

		e.g.: message is "x1[LF]0"
		if 0 ⟶ "x10" ⟶ ⠭⠼⠁⠚   
		if 1 ⟶ "x1"|"0" ⟶ ⠭⠼⠁|⠼⠚ 
	*/
	#define LF_IS_EOM true
#endif
#ifndef SERIAL_NA_IS_EOM
	/*
		Serial Not Available is End Of Message
		If 0, concatinates messages before and after Serial not available

		e.g.: message is "x1[Serial NA]0"
		if 0 ⟶ "x10" ⟶ ⠭⠼⠁⠚   
		if 1 ⟶ "x1"|"0" ⟶ ⠭⠼⠁|⠼⠚ 
	*/
	#define SERIAL_NA_IS_EOM false
#endif


byte brailleCells;
