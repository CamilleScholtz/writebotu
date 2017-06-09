#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

void Drawer::Goto(int degree, const int steps,
	const unsigned int interval) {
	// Make degree actually a degree.
	degree %= 360;

	// TODO: Now think of some algorithm that does this.
	switch (degree) {
	case 0:
		Turn(-steps, steps, interval, interval);
		break;
	case 90:
		Turn(steps/2, steps, interval, interval*2);
		break;
	case 180:
		Turn(steps, -steps, interval, interval);
		break;
	case 270:
		Turn(-steps, -steps/2, interval*2, interval);
		break;
	}
}

void Drawer::Low() {
	lstepper.Low();
	rstepper.Low();
}

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
					lstepper.Step(li);
					li++;
				} else {
					lstepper.Step(li);
					li--;
				}
				// TODO: Should I move this down?
				llast = now;
			}
		}

		if (now - rlast >= linterval) {
			if (ri >= 0 && ri <= abs(rsteps)) {
				if (rsteps > 0) {
					rstepper.Step(ri);
					ri++;
				} else {
					rstepper.Step(ri);
					ri--;
				}
				// TODO: Should I move this down?
				rlast = now;
			}
		}
	}
}
