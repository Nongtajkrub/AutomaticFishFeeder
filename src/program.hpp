#pragma once

#include "program_data.hpp"
#include "feeder.hpp"
#include "netpie.hpp"

namespace Program 
{
	enum class Status {
		NONE,
		ERROR
	};

	class Runner {
	private:
		Status status;
		const struct Data& program_data;

		Netpie netpie;
		Feeder feeder;

	public:
		Runner(const struct Data& program_data);

	public:
		void setup();
		void loop();
		void end();
		Status get_status();
	};
}
