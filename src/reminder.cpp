#include "reminder.hpp"

using namespace Time;

Reminder::Reminder(NTPTimer* timer, u16 max_remind, Unit time_unit) :
    timer(timer), max_remind(max_remind), time_unit(time_unit)
{
    this->remind = new String[max_remind];
}

Reminder::~Reminder() {
    delete[] this->remind;
}

u8 Reminder::add(const String& time) {
    i32 empty_remind;

    if (isDupeRemind(time)) {
		return 0;
    }
    
    // look for empty space in remind to store new remind
    empty_remind = this->findRemind("");
    // not enough space to store new remind
    if (empty_remind == -1) {
		return 1;
    } 

    this->remind[empty_remind] = time;
    return 0;
}

u8 Reminder::del(const String& time) {
    i32 remind = this->findRemind(time);
   
    // the remind does not exsist cant be delete
    if (remind == -1) {
		return 1;
    }

    this->remind[remind].clear();
    return 0;
}

bool Reminder::check() {
    String current_time = this->timer->time(this->time_unit);

    for (u16 i = 0; i < this->max_remind; i++) {
		if (remind[i].isEmpty()) {
	    	continue;
		} 
		if (this->remind[i] == current_time) {
	    	return true;
		}	
    }

    return false;
}

bool Reminder::isDupeRemind(const String& time) {
    return (this->findRemind(time) != -1) ? true : false;
}

i32 Reminder::findRemind(const String& time) {
    for (u16 i = 0; i < this->max_remind; i++) {
		if (this->remind[i] == time) {
			return i;
		}
    }

    return -1;
}

