#ifndef DRAWER_H
#define DRAWER_H

#include <stdlib.h>

#include "stepper.h"

// Drawer is class for simpler interaction with *multiple* stepper
// motors. It also has some neat functions to make drawing easier.
class Drawer {
private:
	// The steppers we want to use.
	Stepper lstepper, rstepper;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper);

	// Move makes the stepper motors move. The lstep parameter
	// establishes how many steps the left stepper motor shoud make
	// and the rstep parameter establishes how many steps the right
	// stepper motor shoud make. if the step paramate contains a
	// negative value the steppers will step in a counter clockwise
	// direcection. The interval parameter is optional.
	void Move(int lsteps, int rsteps, int interval=3);
};

#endif
