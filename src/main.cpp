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

	pinMode(AUTO_PIN,  INPUT);
	pinMode(LATCH_PIN, OUTPUT);
	pinMode(DATA_PIN,  OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);

	countBrailleCells();
	buffer.initialize();
	
	proceedButton = new CyclingButton(BUTTON_PIN);
}

void loop() {
	if (proceedButton->clicked() && readyToShow())
		buffer.show();
}
