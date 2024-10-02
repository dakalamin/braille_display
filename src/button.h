#pragma once

#include <Arduino.h>


#define BUTTON_CLICK_MS 100
#define BUTTON_CYCLE_MS 1000

class Button {
protected:
	Button(byte pin, bool isCycling) : _pin(pin), isCycling(isCycling) {
		pinMode(_pin, INPUT_PULLUP);
	}

public:
	Button(byte pin) : Button(pin, false) { }

	bool clicked() {
		delay(MIN_DELAY_MS);  // digitalRead(...) needs a small delay between calls

		bool state = !digitalRead(_pin);
		uint32_t timeDeltaMS = millis() - _timerMS;

		if (state && !_flag && timeDeltaMS > clickMS) {
			_flag    = true;
			_timerMS = millis();
			return true;
		}
		if (isCycling && state && _flag && timeDeltaMS > cycleMS) {
			_timerMS = millis();
			return true;
		}
		if (!state && _flag) {
			_flag    = false;
			_timerMS = millis();
		}

		return false;
	}

public:
	const bool isCycling;
	uint16_t clickMS = BUTTON_CLICK_MS;
	uint16_t cycleMS = BUTTON_CYCLE_MS;
private:
	byte     _pin;
	bool     _flag  = false;
	uint32_t _timerMS = 0;
};

class CyclingButton : public Button {
public:
	CyclingButton(byte pin) : Button(pin, true) { }
};
