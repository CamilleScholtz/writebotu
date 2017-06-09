#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

// TODO: This function could use some simplification.
void Drawer::Turn(const int lsteps, const int rsteps,
	const unsigned int linterval, const unsigned int rinterval) {
	millis_t llast = 0;
	millis_t rlast = 0;

	int li = 0;
	if (lsteps < 0) {
		li = abs(lsteps);
	}
	int ri = 0;
	if (rsteps < 0) {
		ri = abs(rsteps);
	}

	while ((li >= 0  && li <= abs(lsteps)) || (ri >= 0  && ri <=
		abs(rsteps))) {
		millis_t now = millis_get();

		if (now - llast >= rinterval) {
			if (li >= 0 && li <= abs(lsteps)) {
				if (lsteps > 0) {
					lstepper.Step(li, 0);
					li++;
				} else {
					lstepper.Step(li, 0);
					li--;
				}
				// TODO: Should I move this down?
				llast = now;
			}
		}

		if (now - rlast >= linterval) {
			if (ri >= 0 && ri <= abs(rsteps)) {
				if (rsteps > 0) {
					rstepper.Step(ri, 0);
					ri++;
				} else {
					rstepper.Step(ri, 0);
					ri--;
				}
				// TODO: Should I move this down?
				rlast = now;
			}
		}
	}
}

void Drawer::Goto(int degree, const int steps) {
	// Make degree actually a degree.
	degree %= 360;
	int i = 1;

	// TODO: Now think of some algorithm that does this.
	switch (degree) {
	case 0:
		Turn(-steps, steps);
		break;
	case 90:
		Turn(steps/2, steps, i, i*2);
		break;
	case 180:
		Turn(steps, -steps);
		break;
	case 270:
		Turn(steps, steps/2, i*2, i);
		break;
	}
}
