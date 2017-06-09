#include "util.h"

// Delay sleeps for a specified amount of milliseconds, necause the
// _delay_ms() builtin doesn't allow variables as input.
void Delay(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms(1);
	}
}
