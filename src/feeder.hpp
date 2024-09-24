#pragma once

#include "program_data.hpp"
#include "reminder.hpp"
#include "servo.hpp"
#include "netpie.hpp"
#include "type.hpp"

namespace Program {
	class Feeder {
	private:
		const struct FeederData& feeder_data;

		i8 food_remaining;
		// how much food can be left before a empty warning is trigger
		u8 low_food_threshold;
		// how many time to discharge the food per one feeding session 
		u8 discharge_per_session;
		// how mayny time can be the food be discharge before the feeder
		// get empty
		u16 feeding_before_empty;
		// how much the servo have to turn to discharge the food
		u16 servo_discharge_angle;

		// these are to prevent sending dupe data to netpie
		bool food_low;
		bool food_empty;

		MyServo::ServoControl servo_controler;
		Time::Reminder reminder;
		Netpie& netpie;

	public:
		Feeder(const struct FeederData& feeder_data, Netpie& netpie);
		~Feeder() = default;
	
	public:
		void setup();
		void loop();

	private:
		void add_reminder(const u8 feeding_time[2]);

		void discharge_food();
		void calculate_food_lose();
		void feed();

		void request_food_discharge(u8 food_remaining);
	};
}
