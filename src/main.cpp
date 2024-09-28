#include <Arduino.h>

#include "buffer.h"
#include "button.h"
#include "config.h"
#include "translation.h"


Button* proceedButton;

void setup() {
	Serial.begin(BAUD_RATE);
	Serial.println();

	proceedButton = new Button(buttonPin);

	pinMode(latchPin, OUTPUT);
	pinMode(dataPin,  OUTPUT);
	pinMode(clockPin, OUTPUT);

	clearBuffer();
}

void loop() {
	if (proceedButton->clicked() && prepareToShow())
		showBuffer();
}