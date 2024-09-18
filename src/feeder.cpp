#include "feeder.hpp"

#define DEF_FOOD_CAPACITY 100
#define DEF_MAX_REMIND_COUNT 5

namespace Program {
	Feeder::Feeder(const struct Data& program_data, Netpie& netpie) :
		program_data(program_data),
		food_remaining(DEF_FOOD_CAPACITY),
		empty_threshold(program_data.EMPTY_THRESHOLD),
		discharge_per_session(program_data.DISCHARGE_PER_SESSION),
		feeding_before_empty(program_data.FEEDING_BEFORE_EMPTY),
		servo_discharge_angle(program_data.SERVO_DISCHARGE_ANGLE),
		servo_controler(),
		reminder(program_data.NTP_CLIENT, DEF_MAX_REMIND_COUNT),
		netpie(netpie)
	{}

	void Feeder::setup() {
		this->servo_controler.attach(program_data.SERVO_PIN);
		add_reminder(program_data.FEEDING_TIME1);
		add_reminder(program_data.FEEDING_TIME2);
		add_reminder(program_data.FEEDING_TIME3);
		add_reminder(program_data.FEEDING_TIME4);
		add_reminder(program_data.FEEDING_TIME5);
	}

	void Feeder::loop() {
		reminder.loop();

		// do nothing if no reminder is trigger
		if (!reminder.check()) {
			return;
		}

		// discharge food
		for (u8 i = 0; i < this->discharge_per_session; i++) {
			if (is_low_food()) {
				this->status = FeederStatus::LOW_FOOD;
				this->netpie.request<bool>(
					NetpieRequest::FOOD_EMPTY_WARNING,
					true
					);
				break;
			}
			Serial.println("Feeding");
			feed();
		}

		if (!this->netpie.request<u8>(
				NetpieRequest::FODD_DISCHARGE,
				this->food_remaining
				)
			) {
		};
	}

	void Feeder::add_reminder(const u8 feeding_time[2]) {
		if (feeding_time[0] != 255 && feeding_time[1] != 255) {
			this->reminder.add(feeding_time[0], feeding_time[1]);
		}
	}

	void Feeder::feed() {
		/*
		this->servo_controler.turn(
			this->servo_discharge_angle,
			MyServo::Mode::TOURQE
			);
		this->servo_controler.turn(0, MyServo::Mode::SPEED);
		*/

		this->food_remaining -= (u8)round(
			(f32)DEF_FOOD_CAPACITY / (f32)this->feeding_before_empty
			);
	}

	bool Feeder::is_low_food() {
		return (this->food_remaining < empty_threshold);
	}
}
