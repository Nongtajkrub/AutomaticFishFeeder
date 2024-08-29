#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#include "type.hpp"
#include "timer.hpp"
#include "reminder.hpp"
#include "ui.hpp"

namespace Program {
	class Runner {
		private:
			// error
			static u8 last_err;
			// time
			static WiFiUDP udp;
			static Time::NTPTimer timer;
			static Time::Reminder remind;
			// ui
			static LcdI2cUi::LcdI2cUi_Text welcom_txt;

		public:
			Runner() { return; };
			~Runner() = default;

		public:
			static void init_ui();
			static u8 main();

			static u8 get_last_error();
	};
}
