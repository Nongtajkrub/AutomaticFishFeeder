#pragma once

#include "program_data.hpp"
#include "mqtt.hpp"

namespace Program {
	enum class NetpieRequest {
		NONE,
		FODD_DISCHARGE,
		FOOD_LOW_WARNING,
		FOOD_EMPTY_WARNING
	};

	class Netpie{
	private:
		const struct Data& program_data;
		WiFiClient wifi_client;
		Mqtt::Client mqtt;

	public:
		Netpie(const struct Data& program_data);
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
				case NetpieRequest::FOOD_LOW_WARNING:
					if (!handle_food_low_warning_request(param)) {
						return false;
					}
					break;
				case NetpieRequest::FOOD_EMPTY_WARNING:
					if (!handle_food_empty_warning_request(param)) {
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
		bool handle_food_discharge_request(u8 food_remaining);
		bool handle_food_low_warning_request(bool is_low_food);
		bool handle_food_empty_warning_request(bool is_food_empty);
	};
}
