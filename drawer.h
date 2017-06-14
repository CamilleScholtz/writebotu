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

	// The interval our steppers should use in us.
	const unsigned int interval;

	// The distance between the two stepper motors in mm.
	const float width;

	// The vertical distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const float height;

	// The horizonal distance between the stepper motors and the point
	// of origin (0,0) in mm.
	const float offset;

	// Scale sets the scale of our produced writings.
	const float scale;

	// Our current cord lengths.
	float cllen = sqrt((offset*offset)+(height*height));
	float crlen = sqrt((width-offset)*(width-offset)+(height*height));

	// Our current pen position.
	float cx = 0;
	float cy = 0;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int interval=3000, const float width=565,
		const float height=450, const float offset=165,
		const unsigned int scale=18);

	// Goto moves the pen to the given coordinates.
	void Goto(float x, float y);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Turn turns the stepper motors x amount of steps. {l,r}direction
	// setting the direction, 0 being countclockwise and 1 being
	// clockwise, {l/r}steps sets the amount of steps and
	// {l/r}interval sets the delay between each step.
	void Turn(const bool ldirection, const bool rdirection,
		const unsigned int lsteps, const unsigned int rsteps,
		const unsigned int linterval=3000,
		const unsigned int rinterval=3000);
};

#endif
