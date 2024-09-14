#pragma once

#include "timer.hpp"

namespace Program {
	struct Data {
		// netpie
		const char* MQTT_SERVER;
		const char* MQTT_CLIENT_ID;
		const char* MQTT_USERNAME;
		const char* MQTT_PASSWORD;
		const u16 MQTT_PORT;

		// feeder
		const u8 EMPTY_THRESHOLD;
		const u8 DISCHARGE_PER_SESSION;
		const u16 FEEDING_BEFORE_EMPTY;
		const u16 SERVO_DISCHARGE_ANGLE;
		const u8 SERVO_PIN;
		Time::Timer *const TIMER;
		const char* FEEDING_TIME1;
		const char* FEEDING_TIME2;
		const char* FEEDING_TIME3;
		const char* FEEDING_TIME4;
		const char* FEEDING_TIME5;
	};
}
