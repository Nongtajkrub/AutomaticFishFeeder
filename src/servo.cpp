#include "servo.hpp"

#define TURN_DELAY 10

using namespace _Servo;

ServoControl::ServoControl() :
	Servo()
{
	this->reset();
}

void ServoControl::turn(u16 deg, Mode mode) {
	switch (mode) {
		case Mode::HIGH_TOURQE:
			if (deg > this->curr_deg) {
				this->turn_forward(deg);
			} else if (deg < this->curr_deg) {
				this->turn_backward(deg);
			} 
			break;
		case Mode::HIGH_SPEED:
			this->write(deg);
			break;
	}

	this->curr_deg = deg;
}

void ServoControl::reset() {
	this->write(0);
	this->curr_deg = 0;
}

void ServoControl::turn_forward(u16 deg) {
	for (u16 i = this->curr_deg; i < deg; i++) {
		this->write(i);
		delay(TURN_DELAY);
	}
}

void ServoControl::turn_backward(u16 deg) {
	for (i16 i = this->curr_deg; i >= deg; i--) {
		this->write(i);
		delay(TURN_DELAY);
	}
}
