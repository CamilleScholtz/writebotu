#ifndef UTIL_H
#define UTIL_H

#include <util/delay.h>

namespace Util {
	/// delay sleeps for a specified amount of milliseconds. This is a
	/// hack around the `_delay_ms()` builtin because it doesn't allow
	/// for variables as input.
	void delay(unsigned ms);
};

#endif
