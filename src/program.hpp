#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#include "type.hpp"
#include "timer.hpp"
#include "reminder.hpp"
//#include "ui.hpp"

namespace Program {
	class Runner {
		private:
			u8 last_err;

			WiFiUDP udp;
			NTPTimer *timer;
			Reminder *remind;

		public:
			// take in ssid and password because it might need
			// to be change offten
			Runner(const String& wifi_s, const String& wifi_p);
			~Runner();

		public:
			u8 main(u16 loop_delay);

			u8 get_last_error();

		private:
			bool setup_wifi(const String& ssid, const String& pass);
	};
}
