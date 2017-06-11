#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	const unsigned int interval, const unsigned int width,
	const unsigned height):
	lstepper(lstepper), rstepper(rstepper), interval(interval),
	width(width), height(height)
{}

void Drawer::Goto(const unsigned int x, const unsigned int y) {
	float llen = sqrt((x*x)+(height-y)*(height-y));
	float rlen = sqrt((width-x)*(width-x)+(height-y)*(height-y));

	int lsteps = round((llen-cllen)*10);
	int rsteps = round((rlen-crlen)*10);

	Turn(lsteps, -rsteps);

	cllen = llen;
	crlen = rlen;
	cx = x;
	cy = y;
}

void Drawer::Low() {
	lstepper.Low();
	rstepper.Low();
}

// TODO: This function could use some simplification.
// TODO: Make chords move as fast as each other automatically.
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
