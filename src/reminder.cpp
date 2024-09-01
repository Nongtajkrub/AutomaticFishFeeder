#include "reminder.hpp"

Time::Reminder::Reminder(NTPTimer* timer, u16 max_remind, Unit time_unit) :
    m_timer(timer), m_max_remind(max_remind), m_time_unit(time_unit)
{
    m_remind = new String[max_remind];
}

Time::Reminder::~Reminder() {
    delete[] m_remind;
}

u8 Time::Reminder::add(const String& time) {
    i32 empty_remind;

    if (isDupeRemind(time)) {
		return 0;
    }
    
    // look for empty space in remind to store new remind
    empty_remind = findRemind("");
    // not enough space to store new remind
    if (empty_remind == -1) {
		return 1;
    } 

    m_remind[empty_remind] = time;
    return 0;
}

u8 Time::Reminder::del(const String& time) {
    i32 remind = findRemind(time);
   
    // the remind does not exsist cant be delete
    if (remind == -1) {
		return 1;
    }

    m_remind[remind].clear();
    return 0;
}

bool Time::Reminder::check() {
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

bool Time::Reminder::isDupeRemind(const String& time) {
    return (findRemind(time) != -1) ? true : false;
}

i32 Time::Reminder::findRemind(const String& time) {
    for (u16 i = 0; i < m_max_remind; i++) {
		if (m_remind[i] == time) {
			return i;
		}
    }

    return -1;
}

