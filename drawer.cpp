#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper,
	unsigned interval, float width, float height, float offset,
	unsigned scale):
	lstepper(lstepper), rstepper(rstepper), interval(interval),
	width(width), height(height), offset(offset), scale(scale)
{}

void Drawer::low() {
	lstepper.low();
	rstepper.low();
}

void Drawer::moveto(float x, float y) {
	// Calculate the target cord lengths.
	float llen = sqrt((offset+x)*(offset+x)+(height-y)*(height-y));
	float rlen = sqrt((width-offset-x)*(width-offset-x)+(height-y)*
		(height-y));

	// Calculate the required steps and direction, also apply scaling.
	float lsteps = fabs(llen-cllen)*scale;
	float rsteps = fabs(rlen-crlen)*scale;
	bool ldirection = (llen >= cllen);
	bool rdirection = (rlen <= crlen);

	// Calculate the required intervals. If we don't do this and just
	// use `interval` there will be a (big) possibility that one
	// stepper stops turning earlier than the other, which would
	// result in line with a turn instead of a straight line.
	float linterval = (float)interval;
	float rinterval = (float)interval;
	if (lsteps > rsteps) {
		rinterval = (lsteps*linterval)/rsteps;
	} else if (rsteps > lsteps) {
		linterval = (rsteps*rinterval)/lsteps;
	}

	// Turn the stepper motors till the target cord lengths are
	// achieved.
	turn(ldirection, rdirection, round(lsteps), round(rsteps),
		round(linterval), round(rinterval));

	// Set new values.
	cllen = llen;
	crlen = rlen;
	cx = x;
	cy = y;
}

void Drawer::turn(bool ldirection, bool rdirection, unsigned lsteps,
	unsigned rsteps, unsigned linterval, unsigned rinterval) {
	unsigned long llast = 0;
	unsigned long rlast = 0;
	unsigned li = 0;
	unsigned ri = 0;

	while (li <= lsteps || ri <= rsteps) {
		// Get the current time in μs.
		millis_t now = millis_get()*1000+(TCNT2*4);

		// If the current time minus the last time the left stepper
		// turned is equal or bigger than the interval for the left
		// stepper, turn the stepper.
		if (now-llast >= linterval) {
			if (li <= lsteps) {
				lstepper.step(ldirection);
				li++;

				// TODO: Should I move this down?
				// Save the current time as the last time the left
				// stepper did something.
				llast = now;
			}
		}

		// If the current time minus the last time the right stepper
		// turned is equal or bigger than the interval for the right
		// stepper, turn the stepper.
		if (now-rlast >= rinterval) {
			if (ri <= rsteps) {
				rstepper.step(rdirection);
				ri++;

				// TODO: Should I move this down?
				// Save the current time as the last time the right
				// stepper did something.
				rlast = now;
			}
		}
	}
}
