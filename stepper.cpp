#include "stepper.h"

Stepper::Stepper(volatile uint8_t *ddr, volatile uint8_t *port,
	int pin0, int pin1, int pin2, int pin3):
	ddr(ddr), port(port), pin0(pin0), pin1(pin1), pin2(pin2),
	pin3(pin3)
{
	// This is to allow to write to the given pins.
	*ddr |= _BV(pin0) | _BV(pin1) | _BV(pin2) | _BV(pin3);
}

void Stepper::low() {
	*port = 0b00000000;
}

void Stepper::step(bool direction) {
	if (direction) {
		last = ((last+1)%8+8)%8;
	} else {
		last = ((last-1)%8+8)%8;
	}

	switch (last) {
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

void Stepper::turn(bool direction, unsigned steps,
	unsigned interval) {
	for (unsigned i=0; i<steps; i++) {
		step(direction);
		Util::delay(interval/1000);
	}
}

#if DEBUG
int Stepper::low_test() {
	low();
	assert(*port==0b00000000);

	return 0;
}

int Stepper::step_test() {
	last = 7;
	step(1);
	assert(last==0);

	return 0;
}
#endif
