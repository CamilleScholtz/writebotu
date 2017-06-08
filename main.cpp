#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "drawer.h"
#include "stepper.h"
#include "millis.h"

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
	Stepper lstepper(&PINL_DDR, &PINL_PORT, PINL_0, PINL_1, PINL_2,
		PINL_3);
	Stepper rstepper(&PINR_DDR, &PINR_PORT, PINR_0, PINR_1, PINR_2,
		PINR_3);

	//rstepper.Turn(20000, 2);

	Drawer d(lstepper, rstepper);
	d.Turn(3200, 3200);

	return 0;
}
