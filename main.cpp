#include <avr/io.h>
#include <util/delay.h>

#include "stepper.h"

#define PIN0 PL7
#define PIN1 PD5
#define PIN2 PD3
#define PIN3 PD1

int main(){
	Stepper sr(PIN0, PIN1, PIN2, PIN3);
	sr.Step(90000);

	return 0;
}