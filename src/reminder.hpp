#pragma once

#include "type.hpp"
#include "timer.hpp"

#include <Arduino.h>

namespace Time {
	class Reminder {
		private:
			NTPTimer *const timer;
			String* reminders;
			u16 max_reminders;
			Unit time_unit;

		public:
			Reminder(NTPTimer *const timer, u16 remind_count, Unit time_unit); 
			~Reminder();

		public:
			bool add(const String& time);
			bool del(const String& time);
			bool check();

		private:
			bool is_dupe_remind(const String& time);
			i32 find_remind(const String& time);
	};
};
