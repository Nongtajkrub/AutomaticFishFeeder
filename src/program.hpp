#pragma once

#include "timer.hpp"
#include "reminder.hpp"
#include "netpie.hpp"
#include "ui.hpp"
#include "netpie.hpp"
#include "type.hpp"

namespace Program 
{
	struct Data
	{
		const char* MQTT_SERVER;
		const char* MQTT_CLIENT_ID;
		const char* MQTT_USERNAME;
		const char* MQTT_PASSWORD;
		u16 MQTT_PORT;

		WiFiClient wifi_client;
	};

	class Runner
	{
		private:
			const struct Data m_data;
			Netpie::Client m_netpie;
		
		public:
			Runner(const struct Data& program_data);

		public:
			bool setup();
			bool loop();
	};
}
