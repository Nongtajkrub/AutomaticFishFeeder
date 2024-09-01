#pragma once

#include "type.hpp"

#include <Servo.h>

namespace _Servo {
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
			void turnForward(u16 degree);
			void turnBackward(u16 degree);
	};
}
