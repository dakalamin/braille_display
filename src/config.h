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


#define buttonPin 8
#define dataPin   11  //    DS pin of 74HC595 shift register
#define latchPin  12  // ST_CP pin of 74HC595 shift register
#define clockPin  13  // SH_CP pin of 74HC595 shift register

#ifndef BAUD_RATE
	#define BAUD_RATE 9600
#endif

#define MIN_DELAY_MS 2


const byte BRAILLE_CELLS = 4;


/*
	LF is End Of Message
	If 0, concatinates messages before and after LF symbol

	e.g.: message is "x1[LF]0"
	if 0 ⟶ "x10" ⟶ ⠭⠼⠁⠚   
	if 1 ⟶ "x1"|"0" ⟶ ⠭⠼⠁|⠼⠚ 
*/
#define LF_IS_EOM 0
/*
	Serial Not Available is End Of Message
	If 0, concatinates messages before and after Serial not available

	e.g.: message is "x1[Serial NA]0"
	if 0 ⟶ "x10" ⟶ ⠭⠼⠁⠚   
	if 1 ⟶ "x1"|"0" ⟶ ⠭⠼⠁|⠼⠚ 
*/
#define SERIAL_NA_IS_EOM 0
