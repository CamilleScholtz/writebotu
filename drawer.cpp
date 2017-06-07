#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

void Drawer::Turn(int lsteps, int rsteps, int linterval,
	int rinterval) {
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
		if (li >= 0 && li <= abs(lsteps)) {
			if (lsteps > 0) {
				lstepper.Step(li);
				li++;
			} else {
				lstepper.Step(li);
				li--;
			}
		}
		if (ri >= 0 && ri <= abs(rsteps)) {
			if (rsteps > 0) {
				rstepper.Step(ri);
				ri++;
			} else {
				rstepper.Step(ri);
				ri--;
			}
		}

		// TODO: Should I Delay here or..?
		Delay(linterval+rinterval);
	}
}

void Drawer::Goto(int degree, int steps) {
	// Make degree actually a degree.
	degree %= 360;

	switch (degree) {
	case 0:
		Turn(steps, -steps);
		break;
	case 90:
		Turn(steps/2, steps, 6, 3);
		break;
	case 180:
		Turn(-steps, steps);
		break;
	}
}
