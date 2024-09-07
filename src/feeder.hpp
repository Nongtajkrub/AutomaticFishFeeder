#pragma once

#include "servo.hpp"
#include "type.hpp"

namespace Program {
	class Feeder {
	private:
		u8 food_remaining;
		u8 empty_warning_threshold;
		MyServo::ServoControl servo_controler;

	public:
		Feeder(u8 empty_warning_threshold, u8 servo_pin);

	public:
		void feed();
		bool is_low_food();
	};
}
