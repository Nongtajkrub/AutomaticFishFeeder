#pragma once

#include "program_data.hpp"
#include "mqtt.hpp"

namespace Program {
	enum class NetpieRequest {
		NONE,
		FODD_DISCHARGE,
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
		bool request(NetpieRequest request, void* param);

	private:
		bool handle_food_discharge_request(void* param);
	};
}
