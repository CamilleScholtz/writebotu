#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	const unsigned int interval, const unsigned int width,
	const unsigned int height, const unsigned int offset):
	lstepper(lstepper), rstepper(rstepper), interval(interval),
	width(width), height(height), offset(offset)
{}

// TODO: This function could use some simplification.
void Drawer::Goto(unsigned int x, unsigned int y) {
	//x /= 1000;
	//y /= 1000;

	// Calculate the target cord lengths.
	const unsigned int llen = round(sqrt((offset+x)*(offset+x)+
		(height-y)*(height-y)));
	const unsigned int rlen = round(sqrt((width-offset-x)*
		(width-offset-x)+(height-y)*(height-y)));

	// Calculate the required stepper motor steps.
	// TODO: I should probably make this 80 here a scale variable or
	// something.
	int lsteps = (llen-cllen)*80;
	int rsteps = (rlen-crlen)*80;

	// Calculate the required intervals.
	// TODO: This works for now, but probably won't work on another
	// setup.
	float linterval = interval;
	float rinterval = interval;
	if (abs(lsteps) > abs(rsteps)) {
		rinterval = ((abs(lsteps)/abs(rsteps))*1.333)*interval;
	} else if (abs(rsteps) > abs(lsteps)) {
		linterval = ((abs(rsteps)/abs(lsteps))*1.333)*interval;
	}

	Turn(lsteps, -rsteps, round(linterval), round(rinterval));

	// Set new values.
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
void Drawer::Turn(const int lsteps, const int rsteps,
	const unsigned int linterval, const unsigned int rinterval) {
	unsigned long llast = 0;
	unsigned long rlast = 0;

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
		unsigned long now = millis_get()*1000+(TCNT2*4);

		if (now-llast >= linterval) {
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

		if (now-rlast >= rinterval) {
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
