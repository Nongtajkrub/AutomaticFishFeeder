#include "feeder.hpp"

#define DEF_FOOD_CAPACITY 100
#define DEF_MAX_REMIND_COUNT 5

namespace Program {
	Feeder::Feeder(const struct Data& program_data, Netpie& netpie) :
		food_remaining(DEF_FOOD_CAPACITY),
		empty_threshold(program_data.EMPTY_THRESHOLD),
		discharge_per_session(program_data.DISCHARGE_PER_SESSION),
		feeding_before_empty(program_data.FEEDING_BEFORE_EMPTY),
		servo_discharge_angle(program_data.SERVO_DISCHARGE_ANGLE),
		servo_controler(),
		reminder(program_data.TIMER, DEF_MAX_REMIND_COUNT),
		netpie(netpie)
	{
		this->servo_controler.attach(program_data.SERVO_PIN);
		add_reminders(program_data);
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
			feed();
		}

		this->netpie.request<u8>(
			NetpieRequest::FODD_DISCHARGE,
			this->food_remaining
			);
	}

	void Feeder::add_reminders(const Data& program_data) {
		if (program_data.FEEDING_TIME1 != NULL) {
			this->reminder.add(program_data.FEEDING_TIME1);	
		}
		if (program_data.FEEDING_TIME2 != NULL) {
			this->reminder.add(program_data.FEEDING_TIME2);
		}
		if (program_data.FEEDING_TIME3 != NULL) {
			this->reminder.add(program_data.FEEDING_TIME3);
		}
		if (program_data.FEEDING_TIME4 != NULL) {
			this->reminder.add(program_data.FEEDING_TIME4);
		}
		if (program_data.FEEDING_TIME5 != NULL) {
			this->reminder.add(program_data.FEEDING_TIME5);
		}
	}

	void Feeder::feed() {
		this->servo_controler.turn(
			this->servo_discharge_angle,
			MyServo::Mode::TOURQE
			);
		this->servo_controler.turn(0, MyServo::Mode::SPEED);

		this->food_remaining -= (u8)round(
			(f32)DEF_FOOD_CAPACITY / (f32)this->feeding_before_empty
			);
	}

	bool Feeder::is_low_food() {
		return (this->food_remaining < empty_threshold);
	}
}
