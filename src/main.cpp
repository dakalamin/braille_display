// ⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀
// ⡀⡀⣤⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣤⡀⣤⡀⣤⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣤⡀⣤⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣤⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀
// ⡀⡀⣿⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣶⡀⣶⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣿⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣶⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀
// ⡀⡀⣿⣴⠶⣶⡀⡀⣶⢀⣴⣖⡀⣠⣶⠶⣦⡀⡀⣶⡀⣿⡀⣿⡀⢀⣴⠶⣦⡀⡀⡀⡀⡀⡀⡀⡀⢀⣶⠶⣦⣿⡀⣶⡀⣴⠿⠿⣦⡀⣶⣴⠶⣦⡀⡀⣿⡀⣠⣶⠶⣦⡀⢰⣆⡀⡀⡀⣶⡀⡀
// ⡀⡀⣿⡀⡀⡀⣿⡀⣿⠋⡀⡀⡀⠉⢀⣀⣼⡇⡀⣿⡀⣿⡀⣿⡀⣿⣤⣤⣤⣿⡀⡀⡀⡀⡀⡀⡀⣿⡀⡀⡀⣿⡀⣿⡀⢿⣀⡀⠉⡀⣿⡀⡀⡀⣿⡀⣿⡀⠉⢀⣀⣼⡇⡀⢿⡀⡀⣼⠇⡀⡀
// ⡀⡀⣿⡀⡀⡀⣿⡀⣿⡀⡀⡀⡀⣿⠉⠁⢸⡇⡀⣿⡀⣿⡀⣿⡀⣿⡀⡀⡀⣤⡀⡀⡀⡀⡀⡀⡀⣿⡀⡀⡀⣿⡀⣿⡀⣀⠈⠉⣷⡀⣿⡀⡀⡀⣿⡀⣿⡀⣿⠉⠁⢸⡇⡀⠈⣿⢠⡿⡀⡀⡀
// ⡀⡀⢿⠿⣶⠿⠃⡀⠿⡀⡀⡀⡀⠿⣶⡾⠻⢧⡀⠿⡀⠿⡀⠿⡀⠈⠻⠶⠟⠁⡀⡀⡀⡀⡀⡀⡀⠘⠿⣶⠿⡿⡀⠿⡀⠻⣶⣶⠟⡀⣿⠻⠶⠟⠁⡀⠿⡀⠿⣶⡾⠻⢧⡀⡀⠹⣿⡀⡀⡀⡀
// ⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⠶⠶⠶⠶⠶⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣿⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⣤⣾⠃⡀⡀⡀⡀


#include <Arduino.h>

#include "buffer.h"
#include "button.h"
#include "config.h"
#include "translation.h"


CyclingButton* proceedButton;

void setup() {
	Serial.begin(BAUD_RATE);
	Serial.println();

	proceedButton = new CyclingButton(buttonPin);

	pinMode(latchPin, OUTPUT);
	pinMode(dataPin,  OUTPUT);
	pinMode(clockPin, OUTPUT);

	clearBuffer();
}

void loop() {
	if (proceedButton->clicked() && prepareToShow())
		showBuffer();
}
