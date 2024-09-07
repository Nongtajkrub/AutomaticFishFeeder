#include "program.hpp"
#include "HardwareSerial.h"

#define LOOP_DELAY 10000

//#define NTP_POOL "th.pool.ntp.org"
#define NTP_OFFSET 25200

namespace Program {
	Runner::Runner(const struct Data& program_data) :
		wifi_client(),
		program_data(program_data),
		netpie_client(
			this->wifi_client,
			program_data.MQTT_SERVER,
			program_data.MQTT_PORT
			)
	{}

	bool Runner::send_netpie_data() {
		char msg[this->netpie_data.length() + 1];

		this->netpie_data.toCharArray(msg, this->netpie_data.length() + 1);
		if (this->netpie_client.send_data(
				"@shadow/data/update",
				msg
				) != Netpie::ErrorCode::NONE) {
			return false;
		}

		return true;
	}

	void Runner::setup() {
		this->netpie_client.connect(
			this->program_data.MQTT_CLIENT_ID,
			this->program_data.MQTT_USERNAME,
			this->program_data.MQTT_PASSWORD
			);
	}

	void Runner::loop() {
		this->netpie_client.loop();

		if (!this->send_netpie_data()) {
			this->status = Status::ERROR;
		}

		delay(LOOP_DELAY);
	}
	
	void Runner::end() {
		this->netpie_client.disconnect();
	}

	Status Runner::get_status() { return this->status; }
}
