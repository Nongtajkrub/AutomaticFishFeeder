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

	// if fail return false
	inline bool Netpie::send_data_to_netpie(
		const char* topic,
		const char* payload
		) {
		return (this->mqtt.send_data(topic, payload) != Mqtt::ErrorCode::NONE); 
	}

	bool Netpie::handle_food_discharge_request(u8 food_remaining) {
		String json_data = 
			"{\"data\": {\"food_remaining\": " + String(food_remaining) + "}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (!send_data_to_netpie(UPDATE_SHADOW_TOPIC, msg)) {
			return false;
		}
		return true;
	}

	bool Netpie::handle_food_empty_wanring_request(bool is_low_food) {
		String json_data =
			"{\"data\": {\"food_low\":" +
				String((is_low_food) ? "true" : "false") +
					"}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (!send_data_to_netpie(UPDATE_SHADOW_TOPIC, msg)) {
			return false;
		}
		return true;
	}
}
