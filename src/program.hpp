#pragma once

#include "timer.hpp"
#include "reminder.hpp"
#include "netpie.hpp"
#include "ui.hpp"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#include "type.hpp"

namespace Program {
	class Runner {
		private:
			// error
			static u8 m_last_error;
			// time
			static WiFiUDP m_udp;
			static Time::NTPTimer m_timer;
			static Time::Reminder m_reminder;

		public:
			Runner() { return; };
			~Runner() = default;

		public:
			static void initUi();
			static u8 main();

			static u8 getLastError();
	};
}
