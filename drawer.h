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

	// The distance between the two stepper motors in mm.
	const float width;

	// The vertical distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const float height;

	// The horizonal distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const float offset;

	// Our current cord lengths.
	float cllen = sqrt((offset*offset)+(height*height));
	float crlen = sqrt((width-offset)*(width-offset)+(height*height));

	// Our current pen position.
	float cx = 0;
	float cy = 0;

public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int interval=3000, const float width=565,
		const float height=450, const float offset=165);

	// TODO: Description.
	void Goto(float x, float y);

	// TODO;
	void Intervals(const unsigned int lsteps,
		const unsigned int rsteps, unsigned int &linterval,
		unsigned int &rinterval);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Move makes the stepper motors move. The lstep parameter
	// establishes how many steps the left stepper motor shoud make
	// and the rstep parameter establishes how many steps the right
	// stepper motor shoud make. if the step paramate contains a
	// negative value the steppers will step in a counter clockwise
	// direcection. The interval parameters are optional.
	void Turn(const bool ldirection, const bool rdirection,
		const unsigned int lsteps, const unsigned int rsteps,
		const unsigned int linterval, const unsigned int rinterval);
};

#endif
