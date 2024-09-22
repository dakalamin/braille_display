#pragma once

#include <Arduino.h>

/*
   Normalized UTF-8 char (left padded with 0s to reach 32 bits)
   e.g.: '⠳' (U+2833) - E2 A0 B3 (hex UTF-8) - 00 E2 A0 B3 (hex norm. UTF-8)
*/
typedef uint32_t nchar32_t;
/* 
   Braille 6-dot pattern:
   ❶❹
   ❷❺ ⟶ 0bXX❻❺❹❸❷❶ (e.g. ⠫ = 0b101011)
   ❸❻
*/
typedef uint8_t braille_t;



#define buttonPin 8
#define dataPin   11
#define latchPin  12
#define clockPin  13

#define BAUD_RATE 9600

#define MIN_DELAY_MS 2

const byte BRAILLE_CELLS = 4;

/*
   LF is End Of Message
   if 0 ⟶ "x1[LF]0" ⟶ "x10" ⟶ ⠭⠼⠁⠚   
   if 1 ⟶ "x1[LF]0" ⟶ "x1" | "0" ⟶ ⠭⠼⠁ | ⠼⠚ 
*/
#define LF_IS_EOM 0
