#include "util.h"

void Util::delay(unsigned ms) {
	for (unsigned i=0; i<ms; i++) {
		_delay_ms(1);
	}
}
