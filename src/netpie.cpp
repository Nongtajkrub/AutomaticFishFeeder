#include "netpie.hpp"

#define UPDATE_SHADOW_TOPIC "@shadow/data/update"

namespace Program {
	Netpie::Netpie(const struct Data& program_data) :
		program_data(program_data),
		wifi_client(),
		mqtt(this->wifi_client, program_data.MQTT_SERVER, program_data.MQTT_PORT)
	{}

	bool Netpie::setup() {
		if (
			this->mqtt.connect(
				this->program_data.MQTT_CLIENT_ID,
				this->program_data.MQTT_USERNAME,
				this->program_data.MQTT_PASSWORD
				) != Mqtt::ErrorCode::NONE
			) {
			return false;	
		}
		return true;
	}

	void Netpie::loop() {
		this->mqtt.loop();
	}

	void Netpie::end() {
		this->mqtt.disconnect();
	}

	bool Netpie::handle_food_discharge_request(void* param) {
		u8 food_remaining = *((u8*)param);
		String json_data = 
			"{\"data\": {\"food_remaining\": " + String(food_remaining) + "}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (
			this->mqtt.send_data(
				UPDATE_SHADOW_TOPIC,
				msg
				) != Mqtt::ErrorCode::NONE
			) {
			return false;
		}

		return true;
	}

	bool Netpie::request(NetpieRequest request, void* param) {
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
}
