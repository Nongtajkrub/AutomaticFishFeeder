#pragma once

#include "program_data.hpp"
#include "feeder.hpp"

namespace Program 
{
	enum class Status {
		NONE,
		ERROR
	};

	class Runner {
	private:
		const struct Data& program_data;

		// netpie
		/*
		WiFiClient wifi_client;
		Netpie::Client netpie_client;
		String netpie_data;
		*/

		Feeder feeder;

		Status status;

	public:
		Runner(const struct Data& program_data);

	public:
		void setup();
		void loop();
		void end();
		Status get_status();

	private:
		//bool send_netpie_data();
	};
}
