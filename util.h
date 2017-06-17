#ifndef UTIL_H
#define UTIL_H

#include <util/delay.h>

/// Delay sleeps for a specified amount of milliseconds. Hack around
/// the `_delay_ms()` builtin because that doesn't allow variables as
/// input.
void Delay(int ms);

#endif
