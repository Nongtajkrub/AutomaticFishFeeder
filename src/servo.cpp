#include "servo.hpp"

#define TURN_DELAY 10

namespace MyServo {
	ServoControl::ServoControl() :
		Servo()
	{
		reset();
	}

	void ServoControl::turn(u16 degree, Mode mode) {
		switch (mode) {
			case Mode::TOURQE:
				if (degree > this->servo_degree) {
					turn_forward(degree);
				} else if (degree < this->servo_degree) {
					turn_backward(degree);
				} 
				break;
			case Mode::SPEED:
				write(degree);
				break;
		}

		this->servo_degree = degree;
	}

	void ServoControl::reset() {
		write(0);
		this->servo_degree = 0;
	}

	void ServoControl::turn_forward(u16 degree) {
		for (u16 i = this->servo_degree; i < degree; i++) {
			write(i);
			delay(TURN_DELAY);
		}
	}

	void ServoControl::turn_backward(u16 degree) {
		for (i16 i = this->servo_degree; i >= degree; i--) {
			write(i);
			delay(TURN_DELAY);
		}
	}
}
