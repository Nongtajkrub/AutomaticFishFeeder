#include "feeder.hpp"

#define DEF_FOOD_CAPACITY 100
#define DEF_MAX_REMIND_COUNT 5
#define REFILL_REMINDER_INDEX 0

namespace Program {
	Feeder::Feeder(const struct FeederData& feeder_data, Netpie& netpie) :
		feeder_data(feeder_data),
		food_remaining(DEF_FOOD_CAPACITY),
		low_food_threshold(feeder_data.EMPTY_THRESHOLD),
		discharge_per_session(feeder_data.DISCHARGE_PER_SESSION),
		feeding_before_empty(feeder_data.FEEDING_BEFORE_EMPTY),
		servo_discharge_angle(feeder_data.SERVO_DISCHARGE_ANGLE),
		servo_controler(),
		reminder(feeder_data.NTP_CLIENT, DEF_MAX_REMIND_COUNT),
		netpie(netpie)
	{}

	void Feeder::setup() {
		this->servo_controler.attach(feeder_data.SERVO_PIN);
		this->servo_controler.reset();
		this->netpie.set_low_food_threshold(feeder_data.EMPTY_THRESHOLD);
		this->netpie.set_refill_time(feeder_data.REFILL_TIME);
		this->netpie.set_food_remaining(DEF_FOOD_CAPACITY);

		add_reminder(feeder_data.REFILL_TIME);
		add_reminder(feeder_data.FEEDING_TIME1);
		add_reminder(feeder_data.FEEDING_TIME2);
		add_reminder(feeder_data.FEEDING_TIME3);
		add_reminder(feeder_data.FEEDING_TIME4);
	}

	void Feeder::loop() {
		this->reminder.loop();

		i32 reminder_index;
		if (!this->reminder.check(&reminder_index)) {
			// do nothing if no reminder is trigger
			return;
		}
	
		// refill time reach expect refill
		if (reminder_index == REFILL_REMINDER_INDEX) {
			this->food_remaining = DEF_FOOD_CAPACITY;
			this->netpie.set_food_remaining(this->food_remaining);
			this->food_low = false;
			this->food_empty = false;
		} else {
			feed();
		}
	}

	void Feeder::add_reminder(const Time::reminder_t& reminder) {
		if (reminder.hour != NO_TIME && reminder.minute != NO_TIME) {
			this->reminder.add(reminder.hour, reminder.minute);
		}
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
			if (this->food_remaining == 0) {
				break;
			}
			discharge_food();
			calculate_food_lose();
			Serial.println("Fed");
		}

		this->netpie.set_food_remaining(this->food_remaining);
	}
}
