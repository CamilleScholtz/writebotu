#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	const unsigned int width, const unsigned int dia,
	const unsigned int spr):
	lstepper(lstepper), rstepper(rstepper), width(width), dia(dia),
	spr(spr)
{}

int Drawer::ik(unsigned int x, unsigned int y, unsigned int &l0,
	unsigned int &l1) {
	unsigned int dy = y-0;
	unsigned int dx = x-0;
	l0 = sqrt(dx*dx+dy*dy);
	dx = x-0;
	l1 = sqrt(dx*dx+dy*dy);
}

void Drawer::Goto(unsigned int x, unsigned int y,
	const unsigned int interval) {


	int degree= 2;
	int steps=200;
	// TODO: Now think of some algorithm that does this.
	switch (degree) {
	case 0:
		Turn(-steps, steps, interval, interval);
		break;
	case 90:
		Turn(steps/3, steps, interval, interval*3);
		break;
	case 180:
		Turn(steps, -steps, interval, interval);
		break;
	case 270:
		Turn(steps, steps/3, interval*3, interval);
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
