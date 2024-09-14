#include "program.hpp"

#define LOOP_DELAY 10000

namespace Program {
	Runner::Runner(const struct Data& program_data) :
		program_data(program_data),
		netpie(program_data),
		feeder(program_data, netpie)
	{}
	
	void Runner::setup() {
		this->netpie.setup();
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
