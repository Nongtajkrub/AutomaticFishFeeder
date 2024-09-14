#pragma once

#include "type.hpp"
#include "timer.hpp"

#include <Arduino.h>

namespace Time {
	class Reminder {
	private:
		Timer *const timer;
		u8 current_day;

		String* reminders;
		u16 max_reminders;
		String last_trigger;

	public:
		Reminder(Timer *const timer, u16 max_reminders); 
		~Reminder();

	public:
		void loop();
		bool add(const String& time);
		bool del(const String& time);
		bool check();
		const String& get_last_trigger();

	private:
		void del(u16 reminder);
		bool is_dupe_remind(const String& time);
		i32 find_remind(const String& time);
	};
};
