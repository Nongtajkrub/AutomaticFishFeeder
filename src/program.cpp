#include "program.hpp"

#define LOOP_DELAY 5000

namespace Program {
	Runner::Runner(const struct Data& program_data) :
		program_data(program_data),
		netpie(program_data.netpie),
		feeder(program_data.feeder, netpie)
	{}
	
	void Runner::setup() {
		if (!this->netpie.setup()) {
			Serial.println("Fail to connect to Netpie");
		} else {
			Serial.println("Connected to Netpie");
		}
		feeder.setup();
	}

	void Runner::loop() {
		netpie.loop();
		feeder.loop();

		delay(LOOP_DELAY);
	}
	
	void Runner::end() {
		this->netpie.end();
	}

	Status Runner::get_status() { return this->status; }
}
