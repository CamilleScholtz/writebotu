#include <avr/interrupt.h>
#include <avr/io.h>

#include "drawer.h"
#include "millis.h"
#include "stepper.h"

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
	// Initialize millis library.
	millis_init();

	// Enable interrupts.
	sei();

	// Create our stepper motor objects.
	Stepper lstepper(&PINL_DDR, &PINL_PORT, PINL_0, PINL_1, PINL_2,
		PINL_3);
	Stepper rstepper(&PINR_DDR, &PINR_PORT, PINR_0, PINR_1, PINR_2,
		PINR_3);

	int a = 8;
	Drawer d(lstepper, rstepper);
		// Rectangle.
		d.Goto(0, a);
		Delay(500);
		d.Goto(a, a);
		Delay(500);
		d.Goto(a, 0);
		Delay(500);
		d.Goto(0, 0);
		Delay(500);

		// Cross rectangle.
		d.Goto(a, a);
		Delay(500);
		d.Goto(0, a);
		Delay(500);
		d.Goto(a, 0);
		Delay(500);
		d.Goto(0, 0);
	d.Low();

	return 0;
}
