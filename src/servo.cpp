#include "servo.hpp"

#define TURN_DELAY 10

using namespace _Servo;

ServoControl::ServoControl() :
	Servo()
{
	this->reset();
}

void ServoControl::turn(u16 degree, Mode mode) {
	switch (mode) {
		case Mode::HIGH_TOURQE:
			if (degree > this->servo_degree) {
				this->turn_forward(degree);
			} else if (degree < this->servo_degree) {
				this->turn_backward(degree);
			} 
			break;
		case Mode::HIGH_SPEED:
			this->write(degree);
			break;
	}

	this->servo_degree = degree;
}

void ServoControl::reset() {
	this->write(0);
	this->servo_degree = 0;
}

void ServoControl::turn_forward(u16 degree) {
	for (u16 i = this->servo_degree; i < degree; i++) {
		this->write(i);
		delay(TURN_DELAY);
	}
}

void ServoControl::turn_backward(u16 degree) {
	for (i16 i = this->servo_degree; i >= degree; i--) {
		this->write(i);
		delay(TURN_DELAY);
	}
}
