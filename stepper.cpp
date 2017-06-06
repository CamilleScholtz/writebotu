#include "stepper.h"

Stepper::Stepper(int pin0, int pin1, int pin2, int pin3,
	int interval, int direction) {
	this->pin0 = pin0;
	this->pin1 = pin1;
	this->pin2 = pin2;
	this->pin3 = pin3;

	this->interval = interval;
	this->direction = direction;

	DDRL |= _BV(pin0) | _BV(pin1) | _BV(pin2) | _BV(pin3);
}

void Stepper::Step(int steps) {
	for (int i=0; i<steps; i++) {
		switch (i % 7) {
			case 0:
				PORTL = _BV(pin3);
				break;
			case 1:
				PORTL = _BV(pin1) + _BV(pin3);
				break;
			case 2:
				PORTL = _BV(pin2);
				break;
			case 3:
				PORTL = _BV(pin1) + _BV(pin2);
				break;
			case 4:
				PORTL = _BV(pin1);
				break;
			case 5:
				PORTL = _BV(pin0) + _BV(pin1);
				break;
			case 6:
				PORTL = _BV(pin0);
				break;
			case 7:
				PORTL = _BV(pin0) + _BV(pin3);
				break;
		}

		_delay_ms(interval);
	}
}
