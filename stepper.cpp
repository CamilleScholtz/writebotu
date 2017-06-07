#include "stepper.h"

Stepper::Stepper(int pin0, int pin1, int pin2, int pin3) {
	this->pin0 = pin0;
	this->pin1 = pin1;
	this->pin2 = pin2;
	this->pin3 = pin3;

	// TODO: I probably need to make DDRL a parameter as well.
	// This allows us to write to our pins.
	DDRL |= _BV(pin0) | _BV(pin1) | _BV(pin2) | _BV(pin3);
}

// Step makes the stepper motor take a single step.
void Stepper::Step(int iteration) {
	// TODO: I probably need to make PORTL a parameter as well.
	switch (iteration % 4) {
	case 0:
		PORTL = _BV(pin1);
		break;
	case 1:
		PORTL = _BV(pin2);
		break;
	case 2:
		PORTL = _BV(pin3);
		break;
	case 3:
		PORTL = _BV(pin0);
		break;
	}
}

// Move makes the stepper motor move. The step parameter establishes
// how many steps the stepper motor should take, if the step paramater
// contains a negative value the stepper will step in a counter
// clockwise direcection. The interval parameter is optional.
void Stepper::Move(int steps, int interval) {
	if (steps > 0) {
		for (int i=0; i<steps; i++) {
			Step(i);
			_delay_ms(interval);
		}
	} else {
		for (int i=abs(steps); i>0; i--) {
			Step(i);
			_delay_ms(interval);
		}
	}
}
