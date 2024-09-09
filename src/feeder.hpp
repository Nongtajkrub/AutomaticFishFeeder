#pragma once

#include "program_data.hpp"
#include "servo.hpp"
#include "reminder.hpp"
#include "type.hpp"

namespace Program {
	enum class FeederStatus {
		NORMAL,
		LOW_FOOD
	};

	class Feeder {
	private:
		FeederStatus status;

		u8 food_remaining;
		// how much food can be left before a empty warning is trigger
		u8 empty_threshold;
		// how many time to discharge the food per one feeding session 
		u8 discharge_per_session;
		// how mayny time can be the food be discharge before the feeder
		// get empty
		u16 feeding_before_empty;
		// how much the servo have to turn to discharge the food
		u16 servo_discharge_angle;
		MyServo::ServoControl servo_controler;
		Time::Reminder reminder;

	public:
		Feeder(const struct Data& program_data);
		~Feeder() = default;
	
	public:
		void loop();

	private:
		void add_reminders(const Data& program_data);
		void feed();
		bool is_low_food();
	};
}
