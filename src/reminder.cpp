#include "reminder.hpp"

namespace Time {
	Reminder::Reminder(NTPTimer* timer, u16 max_remind, Unit time_unit) :
		m_timer(timer), m_max_remind(max_remind), m_time_unit(time_unit)
	{
		m_remind = new String[max_remind];
	}

	Reminder::~Reminder() {
		delete[] m_remind;
	}

	u8 Reminder::add(const String& time) {
		i32 empty_remind;

		if (is_dupe_remind(time)) {
			return 0;
		}
		
		// look for empty space in remind to store new remind
		empty_remind = find_remind("");
		// not enough space to store new remind
		if (empty_remind == -1) {
			return 1;
		} 

		m_remind[empty_remind] = time;
		return 0;
	}

	u8 Reminder::del(const String& time) {
		i32 remind = find_remind(time);
	   
		// the remind does not exsist cant be delete
		if (remind == -1) {
			return 1;
		}

		m_remind[remind].clear();
		return 0;
	}

	bool Reminder::check() {
		String current_time = m_timer->time(m_time_unit);

		for (u16 i = 0; i < m_max_remind; i++) {
			if (m_remind[i].isEmpty()) {
				continue;
			} 
			if (m_remind[i] == current_time) {
				return true;
			}	
		}

		return false;
	}

	bool Reminder::is_dupe_remind(const String& time) {
		return (find_remind(time) != -1) ? true : false;
	}

	i32 Reminder::find_remind(const String& time) {
		for (u16 i = 0; i < m_max_remind; i++) {
			if (m_remind[i] == time) {
				return i;
			}
		}

		return -1;
	}
}
