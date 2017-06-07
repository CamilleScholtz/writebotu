#include <avr/io.h>
#include <util/delay.h>

#include "stepper.h"

#define PINL_0 PL7
#define PINL_1 PD5
#define PINL_2 PD3
#define PINL_3 PD1

#define PINR_0 PD6
#define PINR_1 PD4
#define PINR_2 PD2
#define PINR_3 PD0

int main() {
	Stepper sl(PINL_0, PINL_1, PINL_2, PINL_3);
	Stepper sr(PINR_0, PINR_1, PINR_2, PINR_3);

	while (0) {
		for (int i=0; i<500; i++) {
			sl.Move(8);
			sr.Move(-8);
		}
		for (int i=0; i<500; i++) {
			sl.Move(-8);
			sr.Move(8);
		}
	}

	return 0;
}
