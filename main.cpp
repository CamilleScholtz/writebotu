#include <avr/io.h>
#include <util/delay.h>

#include "stepper.h"

#define PINL0 PL7
#define PINL1 PD5
#define PINL2 PD3
#define PINL3 PD1

#define PINR0 PD6
#define PINR1 PD4
#define PINR2 PD2
#define PINR3 PD0

int main(){
	Stepper sl(PINL0, PINL1, PINL2, PINL3);
	Stepper sr(PINR0, PINR1, PINR2, PINR3);

	while (1) {
		sl.Move(1000);
		sr.Move(1000);
	}

	return 0;
}
