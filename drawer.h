#ifndef DRAWER_H
#define DRAWER_H

#include <avr/io.h>
#include <stdlib.h>

#include "millis.h"
#include "stepper.h"
#include "util.h"

// Drawer is class for simpler interaction with *multiple* stepper
// motors. It also has some neat functions to make drawing easier.
class Drawer {
private:
	// The steppers we want to use.
	Stepper lstepper, rstepper;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper);

	// TODO: Description.
	void Goto(int degree, const int steps,
		const unsigned int interval=1);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Move makes the stepper motors move. The lstep parameter
	// establishes how many steps the left stepper motor shoud make
	// and the rstep parameter establishes how many steps the right
	// stepper motor shoud make. if the step paramate contains a
	// negative value the steppers will step in a counter clockwise
	// direcection. The interval parameters are optional.
	void Turn(const int lsteps, const int rsteps,
		const unsigned int linterval=1,
		const unsigned int rinterval=1);
};

#endif
