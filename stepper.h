#include <avr/io.h>
#include <util/delay.h>

class Stepper {
	private:
		int pin0, pin1, pin2, pin3;
		int interval;
		int direction;
	public:
		Stepper(int pin0, int pin1, int pin2, int pin3,
			int interval=2, int direction=0);
		void Step(int steps);
};
