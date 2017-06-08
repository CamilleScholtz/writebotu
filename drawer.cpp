#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

void Drawer::Turn(const int lsteps, const int rsteps,
	const int linterval, const int rinterval) {
	static millis_t llast = 0;
	static millis_t rlast = 0;

	int l = 0;
	int r = 0;
	while (true) {
		millis_t now = millis_get();

		if (now - llast >= 1) {
			lstepper.Step(l, 0);
			llast = now;
			l++;
		}
		if (now - rlast >= 1) {
			rstepper.Step(r, 0);
			rlast = now;
			r++;
		}
	}
}

void Drawer::Goto(int degree, const int steps) {
	// Make degree actually a degree.
	degree %= 360;

	switch (degree) {
	case 0:
		Drawer::Turn(steps, -steps);
		break;
	case 90:
		Drawer::Turn(steps/2, steps, 6, 3);
		break;
	case 180:
		Drawer::Turn(-steps, steps);
		break;
	}
}
