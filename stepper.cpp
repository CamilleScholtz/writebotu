#include "stepper.h"

Stepper::Stepper(int pin0, int pin1, int pin2, int pin3):
	pin0(pin0), pin1(pin1), pin2(pin2), pin3(pin3)
{
	// TODO: I probably need to make DDRL a parameter as well.
	// This allows us to write to our pins.
	DDRL |= _BV(pin0) | _BV(pin1) | _BV(pin2) | _BV(pin3);
}

void Stepper::Step(int iteration) {
	// TODO: I probably need to make PORTL a parameter as well.
	switch (iteration % 7) {
	case 0: // 1000
		PORTL = _BV(pin0);
		break;
	case 1: // 1010
		PORTL = _BV(pin0) + _BV(pin1);
		break;
	case 2: // 0010
		PORTL = _BV(pin1);
		break;
	case 3: // 0110
		PORTL = _BV(pin1) + _BV(pin2);
		break;
	case 4: // 0100
		PORTL = _BV(pin2);
		break;
	case 5: // 0101
		PORTL = _BV(pin2) + _BV(pin3);
		break;
	case 6: // 0001
		PORTL = _BV(pin3);
		break;
	case 7: // 1001
		PORTL = _BV(pin3) + _BV(pin0);
		break;
	}
}

void Stepper::Turn(int steps, int interval) {
	if (steps > 0) {
		for (int i=0; i<steps; i++) {
			Step(i);
			Delay(interval);
		}
	} else {
		for (int i=abs(steps); i>0; i--) {
			Step(i);
			Delay(interval);
		}
	}
}
