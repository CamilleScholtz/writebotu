#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	const unsigned int interval, const float width,
	const float height, const float offset, const unsigned int scale):
	lstepper(lstepper), rstepper(rstepper), interval(interval),
	width(width), height(height), offset(offset), scale(scale)
{}

void Drawer::Goto(float x, float y) {
	// Calculate the target cord lengths.
	const float llen = sqrt((offset+x)*(offset+x)+
		(height-y)*(height-y));
	const float rlen = sqrt((width-offset-x)*
		(width-offset-x)+(height-y)*(height-y));

	// Calculate the required stepper motor steps and direction.
	const float lsteps = fabs(llen-cllen)*scale;
	const float rsteps = fabs(rlen-crlen)*scale;
	const bool ldirection = (llen >= cllen);
	const bool rdirection = (rlen <= crlen);

	// Calculate the required intervals.
	float linterval = (float)interval;
	float rinterval = (float)interval;
	if (lsteps > rsteps) {
		rinterval = (lsteps*linterval)/rsteps;
	} else if (rsteps > lsteps) {
		linterval = (rsteps*rinterval)/lsteps;
	}

	Turn(ldirection, rdirection, round(lsteps), round(rsteps),
		round(linterval), round(rinterval));

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

void Drawer::Turn(const bool ldirection, const bool rdirection,
	const unsigned int lsteps, const unsigned int rsteps,
	const unsigned int linterval, const unsigned int rinterval) {
	unsigned long llast = 0;
	unsigned long rlast = 0;
	unsigned int li = 0;
	unsigned int ri = 0;

	while (li <= lsteps || ri <= rsteps) {
		millis_t now = millis_get()*1000+(TCNT2*4);

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
