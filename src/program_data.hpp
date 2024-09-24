#pragma once

#include "type.hpp"
#include <NTPClient.h>

namespace Program {
	struct NetpieData {
		const char* MQTT_SERVER;
		const char* MQTT_CLIENT_ID;
		const char* MQTT_USERNAME;
		const char* MQTT_PASSWORD;
		const u16 MQTT_PORT;
	};
	
	struct FeederData {
		NTPClient *const NTP_CLIENT;
		const u8 EMPTY_THRESHOLD;
		const u8 DISCHARGE_PER_SESSION;
		const u16 FEEDING_BEFORE_EMPTY;
		const u16 SERVO_DISCHARGE_ANGLE;
		const u8 SERVO_PIN;
		const u8 REFILL_TIME[2];
		const u8 FEEDING_TIME1[2];
		const u8 FEEDING_TIME2[2];
		const u8 FEEDING_TIME3[2];
		const u8 FEEDING_TIME4[2];
	};

	struct Data {
		const struct NetpieData netpie;
		const struct FeederData feeder;
	};
}
