#include "drawer.h"

Drawer::Drawer(Stepper &lstepper, Stepper &rstepper):
	lstepper(lstepper), rstepper(rstepper)
{}

void Drawer::Move(int lsteps, int rsteps, int interval) {
	// Since we use move (which takes at least 8 steps to actually do
	// sometething) we divide our steps by 8, just to stay consitent
	// with our terminology.
	lsteps /= 8;
	rsteps /= 8;

	// Decide if we should feed Move a positive or negitive number.
	// TODO: Can I simplify this?
	int lmove = 8;
	if (lsteps<0) {
		lmove = -8;
	}
	int rmove = 8;
	if (rsteps<0) {
		rmove = -8;
	}

	// Now move our steppers.
	// TODO: Is there actually a better way of moving multiple
	// steppers at the same time? This is a bit crude.
	// TODO: Make interval a paramet as well, or maybe just remove it?
	// TODO: Add delay if l/r < 0 maybe.
	int l = abs(lsteps);
	int r = abs(rsteps);
	while (l>0 || r>0) {
		if (l>0) {
			lstepper.Move(lmove);
			l--;
		}
		if (r>0) {
			rstepper.Move(rmove);
			r--;
		}
	}
}
