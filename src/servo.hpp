#pragma once

#include "type.hpp"

#include <Servo.h>

namespace MyServo {
	enum class Mode {
		HIGH_TOURQE,
		HIGH_SPEED
	};

	class ServoControl : public Servo {
		private:
			u16 m_servo_degree = 0;
  
		public:
			ServoControl();
			~ServoControl() = default;

		public:
			void turn(u16 degree, Mode mode);
			void reset();

		private:
			void turn_forward(u16 degree);
			void turn_backward(u16 degree);
	};
}
