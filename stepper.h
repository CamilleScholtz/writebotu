#ifndef STEPPER_H
#define STEPPER_H

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

// Stepper is class for simpler interaction with stepper motors.
class Stepper {
private:
	// The pins the Stepper class should use to interact with the
	// stepper motor.
	int pin0, pin1, pin2, pin3;

	// The interval in ms at which the stepper motor steps.
	int interval;
public:
	Stepper(int pin0, int pin1, int pin2, int pin3);

	// Step makes the stepper motor take a single step.
	void Step(int iteration);

	// Move makes the stepper motor move. The step parameter
	// establishes how many steps the stepper motor should make, if
	// the step paramate contains a negative value the stepper will
	// step in a counter clockwise direcection. The interval parameter
	// is optional.
	void Move(int steps, int interval=3);
};

#endif
