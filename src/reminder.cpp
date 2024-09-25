#include "reminder.hpp"

namespace Time {
	Reminder::Reminder(NTPClient *const timer, u16 max_reminders) :
		timer(timer),
		max_reminders(max_reminders)
	{
		this->reminders = new reminder_t[max_reminders]();
	}

	Reminder::~Reminder() {
		delete[] this->reminders;
	}

	void Reminder::loop() {
		this->timer->update();

		if (this->timer->getHours() == 0 && this->timer->getMinutes() == 0) {
			for (u16 i = 0; i < this->max_reminders; i++) {
				this->reminders[i].is_trigger = false;
			}
		}
	}

	bool Reminder::add(u8 hour, u8 minute) {
		i32 inactive_reminder;

		if (is_dupe_remind(hour, minute)) {
			return false;
		}
		
		inactive_reminder = find_inactive_reminder();
		// not enough space to store new remind
		if (inactive_reminder == -1) {
			return false;
		} 

		reminder_t new_reminder = {
			.is_active = true,
			.is_trigger = false,
			.hour = hour,
			.minute = minute
		};
		this->reminders[inactive_reminder] = new_reminder;
		return true;
	}

	bool Reminder::del(u8 hour, u8 minute) {
		i32 reminder = find_reminder(hour, minute);
	   
		// the remind does not exsist cant be delete
		if (reminder == -1) {
			return false;
		}

		this->reminders[reminder].is_active = false;
		return true;
	}

	bool Reminder::check(i32* index_buf) {
		i32 reminder = find_reminder(
			this->timer->getHours(),
			this->timer->getMinutes()
			);

		if (reminder != -1 && !this->reminders[reminder].is_trigger) {
			this->reminders[reminder].is_trigger = true;
			if (index_buf != NULL) {
				*index_buf = reminder;
			}
			return true;
		}
		// no reminder was trigger
		if (index_buf != NULL) {
			*index_buf = -1;
		}
		return false;
	}

	void Reminder::del(u16 index) {
		this->reminders[index].is_active = false;
	}

	bool Reminder::is_dupe_remind(u8 hour, u8 minute) {
		return (find_reminder(hour, minute) != -1);
	}

	i32 Reminder::find_reminder(u8 hour, u8 minute) {
		for (u16 i = 0; i < this->max_reminders; i++) {
			if (this->reminders[i].is_active &&
				this->reminders[i].hour == hour &&
				this->reminders[i].minute == minute
				) {
				return i;
			}
		}

		return -1;
	}

	i32 Reminder::find_inactive_reminder() {
		for (u16 i = 0; i < this->max_reminders; i++) {
			if (!this->reminders[i].is_active) {
				return i;
			}
		}

		return -1;
	}
}
