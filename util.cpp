#include "util.h"

void Delay(unsigned ms) {
	for (unsigned i=0; i<ms; i++) {
		_delay_ms(1);
	}
}
