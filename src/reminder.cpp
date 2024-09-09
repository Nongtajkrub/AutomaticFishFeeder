#include "reminder.hpp"

namespace Time {
	Reminder::Reminder(NTPTimer *const timer, u16 max_remind, Unit time_unit) :
		timer(timer), max_reminders(max_remind), time_unit(time_unit)
	{
		this->reminders = new String[max_remind];
	}

	Reminder::~Reminder() {
		delete[] this->reminders;
	}

	bool Reminder::add(const String& time) {
		i32 empty_reminder;

		if (is_dupe_remind(time)) {
			return 0;
		}
		
		// look for empty space in remind to store new remind
		empty_reminder = find_remind("");
		// not enough space to store new remind
		if (empty_reminder == -1) {
			return false;
		} 

		this->reminders[empty_reminder] = time;
		return true;
	}

	bool Reminder::del(const String& time) {
		i32 reminder = find_remind(time);
	   
		// the remind does not exsist cant be delete
		if (reminder == -1) {
			return false;
		}

		this->reminders[reminder].clear();
		return true;
	}

	bool Reminder::check() {
		// check whether any reminder time is the same as the current time
		// if yes return true else return false
		return (find_remind(this->timer->time(this->time_unit)) != -1);
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
