#ifndef STEPPER_H
#define STEPPER_H

#include <avr/io.h>
#include <stdlib.h>

#include "util.h"

// Stepper is class for simpler interaction with stepper motors.
class Stepper {
private:
	// The data direction register Stepper should use to interact
	// with the stepper motor.
	volatile uint8_t *ddr;

	// The IO port Stepper should use to interact with the stepper
	// motor.
	volatile uint8_t *port;

	// The pins the Stepper class should use to interact with the
	// stepper motor.
	const int pin0, pin1, pin2, pin3;

	// The last step our stepper motor has set.
	int step = 0;
public:
	Stepper(volatile uint8_t *ddr, volatile uint8_t *port,
		const int pin0, const int pin1, const int pin2,
		const int pin3);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Step makes the stepper motor take a single step.
	// TODO
	void Step(const bool direction);

	// TODO
	void Turn(const bool direction, const unsigned int steps,
	const unsigned int interval=3);
};

#endif
