#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	const unsigned int interval, const float width,
	const float height, const float offset):
	lstepper(lstepper), rstepper(rstepper), interval(interval),
	width(width), height(height), offset(offset)
{}

void Drawer::Goto(float x, float y) {
	x -= 4000;
	y -= 6000;
	x /= 20;
	y /= 20;

	// Calculate the target cord lengths.
	const float llen = sqrt((offset+x)*(offset+x)+
		(height-y)*(height-y));
	const float rlen = sqrt((width-offset-x)*
		(width-offset-x)+(height-y)*(height-y));

	// Calculate the required stepper motor steps and direction.
	// TODO: 32
	unsigned int lsteps = round(fabs(llen-cllen)*32);
	unsigned int rsteps = round(fabs(rlen-crlen)*32);
	bool ldirection = (llen >= cllen);
	bool rdirection = (rlen <= crlen);

	// Calculate the required intervals and loops.
	unsigned int linterval;
	unsigned int rinterval;
	Intervals(lsteps, rsteps, linterval, rinterval);

	Turn(ldirection, rdirection, lsteps, rsteps, interval, rinterval);

	// Set new values.
	cllen = llen;
	crlen = rlen;
	cx = x;
	cy = y;
}

// TODO: Not 100% perfect yet.
void Drawer::Intervals(const unsigned int lsteps,
	const unsigned int rsteps, unsigned int &linterval,
	unsigned int &rinterval) {
	unsigned int maxsteps;
	unsigned int minsteps;
	if (lsteps > rsteps) {
		minsteps = rsteps;
		maxsteps = lsteps;
	} else {
		minsteps = lsteps;
		maxsteps = rsteps;
	}
	// Prevent divide by zero.
	if (minsteps < 1) {
		minsteps = 1;
	}

	// Calculate the rotate time for each stepper motor.
	float rot = (float)maxsteps*(float)interval;

	//  Calculate delay for motor with the least steps.
	float maxdelay = rot/(float)minsteps;

	// Calculate the number of loops and remainder.
	unsigned int loops = (unsigned int)(maxdelay/(float)65535);
	unsigned int remainder = (unsigned int)(maxdelay-(loops*
		(unsigned int)65535));

	if (lsteps > rsteps){
		linterval = interval;
		rinterval = remainder;
	} else {
		linterval = remainder;
		rinterval = interval;
	}
}

void Drawer::Low() {
	lstepper.Low();
	rstepper.Low();
}

void Drawer::Turn(const bool ldirection, const bool rdirection,
	const unsigned int lsteps, const unsigned int rsteps,
	const unsigned int linterval, const unsigned int rinterval) {
	unsigned long llast = 0;
	unsigned long rlast = 0;

	unsigned int li = 0;
	unsigned int ri = 0;

	while (li <= lsteps || ri <= rsteps) {
		unsigned long now = millis_get()*1000+(TCNT2*4);

		if (now-llast >= linterval) {
			if (li <= lsteps) {
				lstepper.Step(ldirection);
				li++;

				// TODO: Should I move this down?
				llast = now;
			}
		}

		if (now-rlast >= rinterval) {
			if (ri <= rsteps) {
				rstepper.Step(rdirection);
				ri++;

				// TODO: Should I move this down?
				rlast = now;
			}
		}
	}
}
