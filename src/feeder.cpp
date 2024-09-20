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

	bool Feeder::is_low_food() {
		return (this->food_remaining <= empty_threshold);
	}

	void Feeder::discharge_food() {
		this->servo_controler.turn(
			this->servo_discharge_angle,
			MyServo::Mode::TOURQE
			);
		this->netpie.loop(); // prevent losing connection with netpie
		this->servo_controler.turn(0, MyServo::Mode::TOURQE);
	}

	u8 Feeder::calculate_food_lose() {
		i8 food_lose;

		food_lose = (i8)round(
			(f32)DEF_FOOD_CAPACITY / (f32)this->feeding_before_empty
			);
		if (food_lose < 0) {
			food_lose = 0;
		}

		return food_lose;
	}

	void Feeder::feed() {
		for (u8 i = 0; i < this->discharge_per_session; i++) {
			if (this->food_remaining == 0) {
				Serial.println("Food empty");
				break;
			}

			if (is_low_food()) {
				Serial.println("Food Low");
				this->status = FeederStatus::LOW_FOOD;
				this->netpie.request<bool>(
					NetpieRequest::FOOD_EMPTY_WARNING,
					true
					);
			}
			discharge_food();
			this->food_remaining -= calculate_food_lose();
			Serial.println("Fed");
		}

		this->netpie.request<u8>(
			NetpieRequest::FODD_DISCHARGE,
			this->food_remaining
			);
	}
}
