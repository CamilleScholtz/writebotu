#ifndef DRAWER_H
#define DRAWER_H

#include <avr/io.h>
#include <math.h>
#include <stdlib.h>

#include "millis.h"
#include "stepper.h"
#include "util.h"

/// Drawer is class for easier interaction with *multiple* stepper
/// motors.
class Drawer {
private:
	/// The steppers we want to use.
	Stepper lstepper, rstepper;

	/// The minimum intervals our steppers should use in μs.
	const unsigned int interval;

	/// The distance between the two stepper motors in mm.
	const float width;

	/// The vertical distance between the stepper motors and the point
	/// of origin (0,0) in mm. In our case the origin is the bottom
	/// left corner of our drawing area.
	const float height;

	/// The horizonal distance between the stepper motors and the
	/// point of origin (0,0) in mm. Again, our origin is the bottom
	/// left corner of our drawing area.
	const float offset;

	/// The scale of our produced writings.
	const float scale;

	/// Our current cord lengths. This value will be altered later on
	/// by the `Goto()` function to reflect chancges.
	float cllen = sqrt((offset*offset)+(height*height));
	float crlen = sqrt((width-offset)*(width-offset)+(height*height));

	/// Our current pen position. Also this value will be altered
	/// later on by the `Goto()` function to reflect chancges.
	float cx = 0;
	float cy = 0;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int interval=3000, const float width=565,
		const float height=450, const float offset=165,
		const unsigned int scale=16);

	/// Goto moves the pen to the given coordinates.
	void Goto(float x, float y);

	/// Off turns sets all the stepper motor pins to low.
	void Low();

	/// Turn turns the stepper motors `steps` amount of steps.
	/// `ldirection` and `rdirection` setting the respective
	/// directions, 0 being a countclockwise direction and 1 being a
	/// clockwise direction. `linterval` and `rinterval`
	/// set the delay between each step for the respective steppers.
	void Turn(const bool ldirection, const bool rdirection,
		const unsigned int lsteps, const unsigned int rsteps,
		const unsigned int linterval=3000,
		const unsigned int rinterval=3000);
};

#endif
