#include <avr/interrupt.h>
#include <avr/io.h>

#include "drawer.h"
#include "millis.h"
#include "stepper.h"

// Define our left pins and ports.
#define PINL_DDR  DDRL
#define PINL_PORT PORTL
#define PINL_0    PL0
#define PINL_1    PL1
#define PINL_2    PL2
#define PINL_3    PL3

// Define our right pins and ports.
#define PINR_DDR  DDRC
#define PINR_PORT PORTC
#define PINR_0    PC0
#define PINR_1    PC1
#define PINR_2    PC2
#define PINR_3    PC3

int main() {
	// Initialize millis library.
	millis_init();

	// Enable interrupts.
	sei();

	// Create our stepper motor objects.
	Stepper lstepper(&PINL_DDR, &PINL_PORT, PINL_0, PINL_1, PINL_2,
		PINL_3);
	Stepper rstepper(&PINR_DDR, &PINR_PORT, PINR_0, PINR_1, PINR_2,
		PINR_3);

	Drawer d(lstepper, rstepper);
	d.Goto(180, 2000, 2);
	d.Goto(0, 2000, 2);
	d.Goto(90, 1000, 2);
	d.Goto(170, 1000, 2);
	d.Low();

	return 0;
}
