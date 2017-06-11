#ifndef DRAWER_H
#define DRAWER_H

#include <avr/io.h>
#include <math.h>
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

	// The interval our steppers should use.
	const unsigned int interval;

	// The width  and height of the drawing area in cm.
	const unsigned int width;
	const unsigned int height;

	// Our current pen position.
	unsigned int cx = 0;
	unsigned int cy = 0;

	// The current length of our chords.
	float cllen = sqrt(height*height);
	float crlen = sqrt((width*width)+(height*height));
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int interval=2, const unsigned int width=385,
		const unsigned int height=385);

	// TODO: Description.
	void Goto(const unsigned int x, const unsigned int y);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Move makes the stepper motors move. The lstep parameter
	// establishes how many steps the left stepper motor shoud make
	// and the rstep parameter establishes how many steps the right
	// stepper motor shoud make. if the step paramate contains a
	// negative value the steppers will step in a counter clockwise
	// direcection. The interval parameters are optional.
	// TODO: Use interval.
	void Turn(const int lsteps, const int rsteps,
		const unsigned int linterval=2,
		const unsigned int rinterval=2);
};

#endif
