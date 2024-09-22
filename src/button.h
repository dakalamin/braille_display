#pragma once

#include <Arduino.h>


#define BUTTON_CLICK_MS 100
#define BUTTON_CYCLE_MS 1000

class Button {
	public:
		Button(byte pin) {
			_pin = pin;
			pinMode(_pin, INPUT_PULLUP);
		}

		bool clicked() {
			bool state = !digitalRead(_pin);
			uint32_t timeDelta = millis() - _timer;

			if (state && !_flag && timeDelta > BUTTON_CLICK_MS) {
				_flag  = true;
				_timer = millis();
				return true;
			}
			if (state && _flag && timeDelta > BUTTON_CYCLE_MS) {
				_timer = millis();
				return true;
			}
			if (!state && _flag) {
				_flag  = false;
				_timer = millis();
			}

			return false;
		}

	private:
		byte     _pin;
		bool     _flag  = false;
		uint32_t _timer = 0;
};

