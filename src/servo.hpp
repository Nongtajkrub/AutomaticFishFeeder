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
			u16 curr_deg = 0;
  
		public:
			ServoControl();
			~ServoControl() = default;

		public:
			void turn(u16 deg, Mode mode);
			void reset();

		private:
			void turn_forward(u16 deg);
			void turn_backward(u16 deg);
	};
}
