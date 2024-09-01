#include "servo.hpp"

#define TURN_DELAY 10

_Servo::ServoControl::ServoControl() :
	Servo()
{
	reset();
}

void _Servo::ServoControl::turn(u16 degree, Mode mode) {
	switch (mode) {
		case Mode::HIGH_TOURQE:
			if (degree > m_servo_degree) {
				turnForward(degree);
			} else if (degree < m_servo_degree) {
				turnBackward(degree);
			} 
			break;
		case Mode::HIGH_SPEED:
			write(degree);
			break;
	}

	m_servo_degree = degree;
}

void _Servo::ServoControl::reset() {
	write(0);
	m_servo_degree = 0;
}

void _Servo::ServoControl::turnForward(u16 degree) {
	for (u16 i = m_servo_degree; i < degree; i++) {
		write(i);
		delay(TURN_DELAY);
	}
}

void _Servo::ServoControl::turnBackward(u16 degree) {
	for (i16 i = m_servo_degree; i >= degree; i--) {
		write(i);
		delay(TURN_DELAY);
	}
}
