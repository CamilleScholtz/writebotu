#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

void Drawer::Turn(const int lsteps, const int rsteps,
	const int linterval, const int rinterval) {
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
				lstepper.Step(li, 0);
				li++;
			} else {
				lstepper.Step(li, 0);
				li--;
			}
		}
		_delay_ms(linterval);

		if (ri >= 0 && ri <= abs(rsteps)) {
			if (rsteps > 0) {
				rstepper.Step(ri, 0);
				ri++;
			} else {
				rstepper.Step(ri, 0);
				ri--;
			}
		}
		_delay_ms(rinterval);
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
