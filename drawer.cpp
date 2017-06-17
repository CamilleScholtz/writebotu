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

	// Calculate the required stepper motor steps and direction.
	float lsteps = fabs(llen-cllen)*scale;
	float rsteps = fabs(rlen-crlen)*scale;
	bool ldirection = (llen >= cllen);
	bool rdirection = (rlen <= crlen);

	// Calculate the required intervals.
	float linterval = (float)interval;
	float rinterval = (float)interval;
	if (lsteps > rsteps) {
		rinterval = (lsteps*linterval)/rsteps;
	} else if (rsteps > lsteps) {
		linterval = (rsteps*rinterval)/lsteps;
	}

	Drawer::turn(ldirection, rdirection, round(lsteps), round(rsteps),
		round(linterval), round(rinterval));

	// Set new values.
	cx = x;
	cy = y;
	cllen = llen;
	crlen = rlen;
}

void Drawer::turn(bool ldirection, bool rdirection, unsigned lsteps,
	unsigned rsteps, unsigned linterval, unsigned rinterval) {
	unsigned long llast = 0;
	unsigned long rlast = 0;
	unsigned li = 0;
	unsigned ri = 0;

	while (li <= lsteps || ri <= rsteps) {
		millis_t now = millis_get()*1000+(TCNT2*4);

		if (now-llast >= linterval) {
			if (li <= lsteps) {
				lstepper.step(ldirection);
				li++;

				// TODO: Should I move this down?
				llast = now;
			}
		}

		if (now-rlast >= rinterval) {
			if (ri <= rsteps) {
				rstepper.step(rdirection);
				ri++;

				// TODO: Should I move this down?
				rlast = now;
			}
		}
	}
}
