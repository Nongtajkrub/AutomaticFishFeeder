#include "reminder.hpp"

#define DEBUG(MSG) Serial.print(MSG)
#define DEBUGLN(MSG) Serial.println(MSG)

// TODO fix reminder not triggering

namespace Time {
	Reminder::Reminder(Timer *const timer, u16 max_reminders) :
		timer(timer),
		max_reminders(max_reminders),
		current_day(this->timer->day()),
		last_trigger("")
	{
		this->reminders = new String[max_reminders];
	}

	Reminder::~Reminder() {
		delete[] this->reminders;
	}

	void Reminder::loop() {
		DEBUGLN("Reminder loop");

		u8 new_day = this->timer->day();

		DEBUG("Curent day: ");
		DEBUGLN(this->current_day);
		DEBUG("New day: ");
		DEBUGLN(new_day);
		DEBUG("Current time: ");
		DEBUGLN(this->timer->time(Unit::MINUTE));

		// the day has change
		if (current_day != new_day) {
			DEBUGLN("Reminder day change");
			last_trigger.clear();
		}
	}

	bool Reminder::add(const String& time) {
		i32 empty_reminder;

		if (is_dupe_remind(time)) {
			DEBUGLN("Fail to add fine dupe reminde");
			return 0;
		}
		
		// look for empty space in remind to store new remind
		empty_reminder = find_remind("");
		// not enough space to store new remind
		if (empty_reminder == -1) {
			DEBUGLN("No empty spot for remind");
			return false;
		} 

		DEBUGLN("Reminder added reminder");
		this->reminders[empty_reminder] = time;
		return true;
	}

	bool Reminder::del(const String& time) {
		i32 reminder = find_remind(time);
	   
		// the remind does not exsist cant be delete
		if (reminder == -1) {
			DEBUGLN("Fail to delete remind dont excist");
			return false;
		}


		DEBUGLN("Reminder deleted reminder");
		this->reminders[reminder].clear();
		return true;
	}

	bool Reminder::check() {
		DEBUGLN("Checking for trigger reminder");
		i32 reminder = find_remind(this->timer->time(Unit::MINUTE));

		// a reminder was trigger and have never been trigger today
		if (reminder != -1 && this->reminders[reminder] != this->last_trigger) {
			last_trigger = this->reminders[reminder];
			DEBUG("Found trigger reminder: ");
			DEBUGLN(this->last_trigger);
			return true;
		}
		// no reminder was trigger
		DEBUGLN("No trigger reminder");
		return false;
	}

	const String& Reminder::get_last_trigger() {
		return this->last_trigger;
	}

	void Reminder::del(u16 reminder) {
		this->reminders[reminder].clear();
	}

	bool Reminder::is_dupe_remind(const String& time) {
		return (find_remind(time) != -1);
	}

	i32 Reminder::find_remind(const String& time) {
		for (u16 i = 0; i < this->max_reminders; i++) {
			if (this->reminders[i] == time) {
				return i;
			}
		}

		return -1;
	}
}
