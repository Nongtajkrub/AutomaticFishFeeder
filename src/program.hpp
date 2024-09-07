#pragma once

#include "timer.hpp"
#include "reminder.hpp"
#include "ui.hpp"
#include "netpie.hpp"
#include "type.hpp"

namespace Program 
{
	struct Data {
		const char* MQTT_SERVER;
		const char* MQTT_CLIENT_ID;
		const char* MQTT_USERNAME;
		const char* MQTT_PASSWORD;
		const u16 MQTT_PORT;
	};

	enum class Status {
		NONE,
		ERROR
	};

	class Runner {
	private:
		const struct Data& program_data;

		// netpie
		WiFiClient wifi_client;
		Netpie::Client netpie_client;
		String netpie_data;

		// feeder
		u8 food_remaining = 100;

		Status status;

	public:
		Runner(const struct Data& program_data);

	public:
		void setup();
		void loop();
		void end();
		Status get_status();

	private:
		bool send_netpie_data();
	};
}
