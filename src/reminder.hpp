#pragma once

#include "type.hpp"

#include <Arduino.h>
#include <NTPClient.h>

#define NO_TIME 255

namespace Time {
	typedef struct {
		bool is_active;
		bool is_trigger;

		u8 hour;
		u8 minute;
	} reminder_t;

	class Reminder {
	private:
		NTPClient *const timer;

		u16 max_reminders;
		reminder_t* reminders;
		reminder_t temp_reminder;

	public:
		Reminder(NTPClient *const timer, u16 max_reminders); 
		~Reminder();

	public:
		void loop();
		bool add(u8 hour, u8 minute);
		bool del(u8 hour, u8 minute);
		bool check(i32* index_buf);

	private:
		void del(u16 index);
		bool is_dupe_remind(u8 hour, u8 minute);
		i32 find_reminder(u8 hour, u8 minute);
		i32 find_inactive_reminder();
	};
};
