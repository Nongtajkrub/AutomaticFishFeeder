#include "feeder.hpp"

#define DEF_FOOD_CAPACITY 100
#define DEF_MAX_REMIND_COUNT 5

namespace Program {
	Feeder::Feeder(const struct Data& program_data, Netpie& netpie) :
		program_data(program_data),
		food_remaining(DEF_FOOD_CAPACITY),
		low_food_threshold(program_data.EMPTY_THRESHOLD),
		discharge_per_session(program_data.DISCHARGE_PER_SESSION),
		feeding_before_empty(program_data.FEEDING_BEFORE_EMPTY),
		servo_discharge_angle(program_data.SERVO_DISCHARGE_ANGLE),
		servo_controler(),
		reminder(program_data.NTP_CLIENT, DEF_MAX_REMIND_COUNT),
		netpie(netpie)
	{}

	void Feeder::setup() {
		this->servo_controler.attach(program_data.SERVO_PIN);
		this->servo_controler.reset();
		add_reminder(program_data.FEEDING_TIME1);
		add_reminder(program_data.FEEDING_TIME2);
		add_reminder(program_data.FEEDING_TIME3);
		add_reminder(program_data.FEEDING_TIME4);
		add_reminder(program_data.FEEDING_TIME5);
	}

	void Feeder::loop() {
		this->reminder.loop();

		// do nothing if no reminder is trigger
		if (!this->reminder.check()) {
			return;
		} else {
			feed();
		}
	}

	void Feeder::add_reminder(const u8 feeding_time[2]) {
		if (feeding_time[0] != 255 && feeding_time[1] != 255) {
			this->reminder.add(feeding_time[0], feeding_time[1]);
		}
	}

	bool Feeder::check_serious_warning() {
		Serial.println("Food remaining");
		Serial.println(this->food_remaining);
		if (this->food_remaining == 0) {
			Serial.println("Food empty");
			request_food_low_warning(false);
			request_food_empty_warning(true);
			return false;
		}

		if (this->food_remaining <= this->low_food_threshold) {
			Serial.println("Food low");
			request_food_low_warning(true);
		}

		return true;
	}

	void Feeder::discharge_food() {
		this->servo_controler.turn(
			this->servo_discharge_angle,
			MyServo::Mode::TOURQE
			);
		this->netpie.loop(); // prevent losing connection with netpie
		this->servo_controler.turn(0, MyServo::Mode::TOURQE);
	}

	void Feeder::calculate_food_lose() {
		this->food_remaining -= (i8)round(
			(f32)DEF_FOOD_CAPACITY / (f32)this->feeding_before_empty
			); 
		if (this->food_remaining < 0) {
			this->food_remaining = 0;
		}
	}

	void Feeder::feed() {
		for (u8 i = 0; i < this->discharge_per_session; i++) {
			if (!check_serious_warning()) {
				return;
			}
			discharge_food();
			calculate_food_lose();
			Serial.println("Fed");
		}

		check_serious_warning();
		request_food_discharge(this->food_remaining);
	}

	void Feeder::request_food_discharge(u8 food_remaining) {
		if (this->food_remaining == food_remaining) {
			return;
		}
		this->food_remaining = food_remaining;
		this->netpie.request<i8>(
			NetpieRequest::FODD_DISCHARGE,
			food_remaining
			);
	}

	void Feeder::request_food_low_warning(bool food_low) {
		if (this->food_low == food_low) {
			return;
		}
		this->food_low = food_low;
		this->netpie.request<bool>(
			NetpieRequest::FOOD_LOW_WARNING, 
			food_low
			);
	}

	void Feeder::request_food_empty_warning(bool food_empty) {
		if (this->food_empty == food_empty) {
			return;
		}
		this->food_empty = food_empty;
		this->netpie.request<bool>(
			NetpieRequest::FOOD_EMPTY_WARNING,
			food_empty
			);
	}
}
