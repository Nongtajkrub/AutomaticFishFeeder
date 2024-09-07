#include "feeder.hpp"

// how much the servo need to turn to discharge the food
#define SERVO_ANGLE_FOR_DISCHARGE 90
// how many time the feeder can discharge the food before it is empty 
#define FEEDING_AMOUNT_BEFORE_EMPTY 10
#define FOOD_CAPACITY 100

namespace Program {
	Feeder::Feeder(u8 empty_warning_threshold, u8 servo_pin) :
		food_remaining(100),
		empty_warning_threshold(empty_warning_threshold),
		servo_controler()
	{
		this->servo_controler.attach(servo_pin);
	}

	void Feeder::feed() {
		this->servo_controler.turn(
			SERVO_ANGLE_FOR_DISCHARGE,
			MyServo::Mode::TOURQE
			);
		this->servo_controler.turn(0, MyServo::Mode::SPEED);
		this->food_remaining -= FEEDING_AMOUNT_BEFORE_EMPTY / FOOD_CAPACITY;
	}

	bool Feeder::is_low_food() {
		return (this->food_remaining < empty_warning_threshold);
	}
}
