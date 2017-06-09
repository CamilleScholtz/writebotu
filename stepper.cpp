#include "stepper.h"

Stepper::Stepper(volatile uint8_t *ddr, volatile uint8_t *port,
	const int pin0, const int pin1, const int pin2, const int pin3):
	ddr(ddr), port(port), pin0(pin0), pin1(pin1), pin2(pin2),
	pin3(pin3)
{
	// This allows us to write to our pins.
	*ddr |= _BV(pin0) | _BV(pin1) | _BV(pin2) | _BV(pin3);
}

void Stepper::Off() {
	*port = 0b00000000;
}

void Stepper::Step(const int iteration) {
	switch (iteration % 7) {
	case 0:
		*port = _BV(pin0);
		break;
	case 1:
		*port = _BV(pin0) + _BV(pin1);
		break;
	case 2:
		*port = _BV(pin1);
		break;
	case 3:
		*port = _BV(pin1) + _BV(pin2);
		break;
	case 4:
		*port = _BV(pin2);
		break;
	case 5:
		*port = _BV(pin2) + _BV(pin3);
		break;
	case 6:
		*port = _BV(pin3);
		break;
	case 7:
		*port = _BV(pin3) + _BV(pin0);
		break;
	}
}

void Stepper::Turn(const int steps, const unsigned int interval) {
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
