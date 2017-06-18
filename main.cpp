#include <avr/interrupt.h>
#include <avr/io.h>

#include "drawer.h"
#include "millis.h"
#include "stepper.h"
#include "svg.h"

// Define our left pins and ports.
#define PINL_DDR  DDRC
#define PINL_PORT PORTC
#define PINL_0    PC0
#define PINL_1    PC1
#define PINL_2    PC2
#define PINL_3    PC3

// Define our right pins and ports.
#define PINR_DDR  DDRL
#define PINR_PORT PORTL
#define PINR_0    PL0
#define PINR_1    PL1
#define PINR_2    PL2
#define PINR_3    PL3

int main() {
	// Initialize the millis library.
	millis_init();

	// Enable interrupts.
	sei();

	// Create Stepper objects.
	Stepper lstepper(&PINL_DDR, &PINL_PORT, PINL_0, PINL_1, PINL_2,
		PINL_3);
	Stepper rstepper(&PINR_DDR, &PINR_PORT, PINR_0, PINR_1, PINR_2,
		PINR_3);

	// Initialize the Drawer object and draw the generated svg file.
	Drawer d(lstepper, rstepper);
	svg(d);
	d.low();

	return 0;
}
