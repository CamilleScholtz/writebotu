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

	// The width between the two stepper motors.
	const unsigned int width;

	// The diameter of our stepper wheels in cm.
	const unsigned int dia;

	// The steppers steps per revolution.
	const unsigned int spr;

	// The circumfence.
	const unsigned int cir = dia*M_PI;

	// Thread per step.
	const unsigned int tps = cir/spr;

	// Our current pen position.
	unsigned int cx=width/2, cy=100;

	// Inverse kinematics calculate function.
	int ik(unsigned int x, unsigned int y, unsigned int &l0,
		unsigned int &l1);
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		const unsigned int width, const unsigned int dia,
		const unsigned int spr);

	// TODO: Description.
	void Goto(unsigned int x, unsigned int y,
		const unsigned int interval=2);

	// Off turns sets all the stepper motor pins to low.
	void Low();

	// Move makes the stepper motors move. The lstep parameter
	// establishes how many steps the left stepper motor shoud make
	// and the rstep parameter establishes how many steps the right
	// stepper motor shoud make. if the step paramate contains a
	// negative value the steppers will step in a counter clockwise
	// direcection. The interval parameters are optional.
	void Turn(const int lsteps, const int rsteps,
		const unsigned int linterval=2,
		const unsigned int rinterval=2);
};

#endif
