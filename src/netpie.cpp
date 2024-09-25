#include "netpie.hpp"
#include "WString.h"

#define UPDATE_SHADOW_TOPIC "@shadow/data/update"

namespace Program {
	Netpie::Netpie(const struct NetpieData& netpie_data) :
		netpie_data(netpie_data),
		wifi_client(),
		mqtt(this->wifi_client, netpie_data.MQTT_SERVER, netpie_data.MQTT_PORT)
	{}

	bool Netpie::setup() {
		if (
			this->mqtt.connect(
				this->netpie_data.MQTT_CLIENT_ID,
				this->netpie_data.MQTT_USERNAME,
				this->netpie_data.MQTT_PASSWORD
				) != Mqtt::ErrorCode::NONE
			) {
			return false;
		}
		return true;
	}

	void Netpie::loop() {
		this->mqtt.loop();

		if (!this->mqtt.is_connect()) {
			this->mqtt.connect(
				this->netpie_data.MQTT_CLIENT_ID,
				this->netpie_data.MQTT_USERNAME,
				this->netpie_data.MQTT_PASSWORD
				);
		};
	}

	void Netpie::end() {
		this->mqtt.disconnect();
	}

	// if fail return false
	inline bool Netpie::send_data_to_netpie(
		const char* topic,
		const char* payload
		) {
		return (this->mqtt.send_data(topic, payload) == Mqtt::ErrorCode::NONE); 
	}

	bool Netpie::set_refill_time(const Time::reminder_t& refill_time) {
		String format_time = 
			String(refill_time.hour) + " : " + String(refill_time.minute);
		String json_data = 
			"{\"data\": {\"refill_time\": " + format_time + "}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (!send_data_to_netpie(UPDATE_SHADOW_TOPIC, msg)) {
			return false;
		}
		return true;
	}

	bool Netpie::set_low_food_threshold(u8 threshold) {
		String json_data = 
			"{\"data\": {\"low_food_threshold\": " + String(threshold) + "}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (!send_data_to_netpie(UPDATE_SHADOW_TOPIC, msg)) {
			return false;
		}
		return true;

	}

	bool Netpie::set_food_remaining(u8 food_remaining) {
		String json_data = 
			"{\"data\": {\"food_remaining\": " + String(food_remaining) + "}}";
		char msg[json_data.length() + 1];
		json_data.toCharArray(msg, sizeof(msg));

		if (!send_data_to_netpie(UPDATE_SHADOW_TOPIC, msg)) {
			return false;
		}
		return true;
	}
}
