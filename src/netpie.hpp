// if you look at this system and think that it is over complcated.
// it was originally design for a more complicated situation than this.

#pragma once

#include "program_data.hpp"
#include "mqtt.hpp"

namespace Program {
	enum class NetpieRequest {
		NONE,
		FODD_DISCHARGE
	};

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

		template<typename T>
		bool request(NetpieRequest request, T param) {
			switch (request) {
				case NetpieRequest::FODD_DISCHARGE:
					if (!handle_food_discharge_request(param)) {
						return false;
					}
					break;
				default:
					break;
			}

			return true;
		}

	private:
		inline bool send_data_to_netpie(const char* topic, const char* payload);
		bool handle_set_refill_time_request(u8 refill_time[2]);
		bool handle_low_food_threshold_request(u8 threshold);
		bool handle_food_discharge_request(u8 food_remaining);
	};
}
