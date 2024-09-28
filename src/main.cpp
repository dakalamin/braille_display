#include <Arduino.h>

#include "buffer.h"
#include "button.h"
#include "config.h"
#include "translation.h"


Button button(buttonPin);

void setup() {
	Serial.begin(BAUD_RATE);
	Serial.println();

	pinMode(latchPin, OUTPUT);
	pinMode(dataPin,  OUTPUT);
	pinMode(clockPin, OUTPUT);

	clearBuffer();
}

void loop() {
	if (button.clicked() && prepareToShow())
		showBuffer();
}