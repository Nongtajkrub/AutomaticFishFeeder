// if you look at this system and think that it is over complcated.
// it was originally design for a more complicated situation than this.

#pragma once

#include "program_data.hpp"
#include "mqtt.hpp"

namespace Program {
	class Netpie{
	private:
		const struct NetpieData& netpie_data;
		WiFiClient wifi_client;
		Mqtt::Client mqtt;

	public:
		Netpie(const struct NetpieData& netpie_data);
		~Netpie() = default;

	public:
		bool setup();
		void loop();
		void end();

		bool set_refill_time(const Time::reminder_t& refill_time);
		bool set_low_food_threshold(u8 threshold);
		bool set_food_remaining(u8 food_remaining);
	
	private:
		inline bool send_data_to_netpie(const char* topic, const char* payload);
	};
}
