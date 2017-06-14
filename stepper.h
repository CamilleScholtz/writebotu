#ifndef STEPPER_H
#define STEPPER_H

#include <avr/io.h>
#include <stdlib.h>

#include "util.h"

// Stepper is class for simpler interaction with stepper motors.
class Stepper {
private:
	// The data direction register we should use to interact with the
	// stepper motor.
	volatile uint8_t *ddr;

	// The IO port we should use to interact with the stepper motor.
	volatile uint8_t *port;

	// The pins we should use to interact with the stepper motor.
	const int pin0, pin1, pin2, pin3;

	// The last step our stepper motor has set.
	int step = 0;
public:
	Stepper(volatile uint8_t *ddr, volatile uint8_t *port,
		const int pin0, const int pin1, const int pin2,
		const int pin3);

	// Off sets all the stepper motor pins to low.
	void Low();

	// Step makes the stepper motor take a single step. The direction
	// parameter set the direction the stepper will step in, 0 being
	// counterclockwise and 1 being clockwise.
	void Step(const bool direction);

	// Turn turns the stepper motor x amount of steps. Direction again
	// setting the direction, steps set the amount of steps and
	// interval sets the delay between each step in us.
	void Turn(const bool direction, const unsigned int steps,
		const unsigned int interval=300);
};

#endif
