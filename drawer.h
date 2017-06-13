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
	const unsigned int width;

	// The vertical distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const unsigned int height;

	// The horizonal distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const unsigned int offset;

	// The distance of the two cords when the pen is is at (0,0) in
	// mm.
	unsigned int cllen = round(sqrt((offset*offset)+(height*height)));
	unsigned int crlen = round(sqrt((width-offset)*(width-offset)+
		(height*height)));

	// Our current pen position.
	unsigned int cx = 0;
	unsigned int cy = 0;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int interval=3000,
		const unsigned int width=520, const unsigned int height=485,
		const unsigned int offset=240);

	// TODO: Description.
	void Goto(unsigned int x, unsigned int y);

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
		const unsigned int linterval=3000,
		const unsigned int rinterval=3000);
};

#endif
