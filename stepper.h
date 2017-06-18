#ifndef STEPPER_H
#define STEPPER_H

#if DEBUG
#include <assert.h>
#endif
#include <avr/io.h>
#include <stdlib.h>

#include "util.h"

/// Stepper is class for easy interaction with stepper motors.
class Stepper {
private:
	/// The data direction register that should be used to interact
	/// with the stepper. The given pins will be written to this
	/// register in order to allow writing to the pins.
	volatile uint8_t *ddr;

	/// The IO port that should be used to interact with the stepper.
	volatile uint8_t *port;

	/// The pins that should be used to interact with the stepper.
	int pin0, pin1, pin2, pin3;

	/// The last step the stepper has set.
	int last = 0;
public:
	Stepper(volatile uint8_t *ddr, volatile uint8_t *port, int pin0,
		int pin1, int pin2, int pin3);

	/// off sets all the steppers pins to low.
	void low();

	/// step makes the stepper motor take a single step. The
	/// `direction` parameter sets the direction the stepper will step
	/// in, 0 being a counterclockwise direction and 1 being a
	/// clockwise direction.
	void step(bool direction);

	/// turn turns the stepper motor `steps` amount of steps.
	/// `direction` again setting the direction we should step in and
	/// `interval` setting the delay between each step in μs.
	void turn(bool direction, unsigned steps, unsigned interval=3000);

	// Various unit tests.
	#if DEBUG
	int low_test();
	int step_test();
	#endif
};

#endif
