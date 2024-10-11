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
#include "utils.h"


CyclingButton* proceedButton;

void setup() {
	Serial.begin(BAUD_RATE);
	Serial.println();

	pinMode(autoPin,  INPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin,  OUTPUT);
	pinMode(clockPin, OUTPUT);

	countBrailleCells();
	buffer.initialize();
	
	proceedButton = new CyclingButton(buttonPin);
}

void loop() {
	if (proceedButton->clicked() && readyToShow())
		buffer.show();
}
