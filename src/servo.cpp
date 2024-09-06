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
			case Mode::HIGH_TOURQE:
				if (degree > m_servo_degree) {
					turn_forward(degree);
				} else if (degree < m_servo_degree) {
					turn_backward(degree);
				} 
				break;
			case Mode::HIGH_SPEED:
				write(degree);
				break;
		}

		m_servo_degree = degree;
	}

	void ServoControl::reset() {
		write(0);
		m_servo_degree = 0;
	}

	void ServoControl::turn_forward(u16 degree) {
		for (u16 i = m_servo_degree; i < degree; i++) {
			write(i);
			delay(TURN_DELAY);
		}
	}

	void ServoControl::turn_backward(u16 degree) {
		for (i16 i = m_servo_degree; i >= degree; i--) {
			write(i);
			delay(TURN_DELAY);
		}
	}
}
