#ifndef STEPPER_H
#define STEPPER_H

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

/// Stepper is class for easy interaction with stepper motors.
class Stepper {
private:
	/// The data direction register we should use to interact with the
	/// stepper motor. We write our pins to this register in order to
	/// allow writing to the pins.
	volatile uint8_t *ddr;

	/// The IO port we should use to interact with the stepper motor.
	volatile uint8_t *port;

	/// The pins we should use to interact with the stepper motor.
	const int pin0, pin1, pin2, pin3;

	/// The last step our stepper motor has set.
	int step = 0;
public:
	Stepper(volatile uint8_t *ddr, volatile uint8_t *port,
		const int pin0, const int pin1, const int pin2,
		const int pin3);

	/// Off sets all the stepper motor pins to low.
	void Low();

	/// Step makes the stepper motor take a single step. The
	/// `direction` parameter set the direction the stepper will step
	/// in, 0 being a counterclockwise direction and 1 being a
	/// clockwise direction.
	void Step(const bool direction);

	/// Turn turns the stepper motor `steps` amount of steps.
	/// `direction` again setting the direction we should step in and
	/// `interval` setting the delay between each step in μs.
	void Turn(const bool direction, const unsigned int steps,
		const unsigned int interval=300);
};

#endif
