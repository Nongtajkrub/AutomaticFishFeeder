#include "reminder.hpp"

Reminder::Reminder(NTPTimer* timer, u16 max_remind, TimeUnit time_unit) :
    timer(timer), max_remind(max_remind), time_unit(time_unit)
{
    this->remind = new String[max_remind];
}

Reminder::~Reminder() {
    delete[] this->remind;
}

u8 Reminder::add(const String& time) {
    i32 emp_remind_ind;

    if (is_dupe_remind(time)) {
		return 0;
    }
    
    // look for empty space in remind to store new remind
    emp_remind_ind = this->find_remind("");
    // not enough space to store new remind
    if (emp_remind_ind == -1) {
		return 1;
    } 

    this->remind[emp_remind_ind] = time;
    return 0;
}

u8 Reminder::del(const String& time) {
    i32 remind_ind = this->find_remind(time);
   
    // the remind does not exsist cant be delete
    if (remind_ind == -1) {
		return 1;
    }

    this->remind[remind_ind].clear();
    return 0;
}

bool Reminder::check() {
    String curr_time = this->timer->time(this->time_unit);

    for (u16 i = 0; i < this->max_remind; i++) {
		if (remind[i].isEmpty()) {
	    	continue;
		} 
		if (this->remind[i] == curr_time) {
	    	return true;
		}	
    }

    return false;
}

bool Reminder::is_dupe_remind(const String& time) {
    return (this->find_remind(time) != -1) ? true : false;
}

i32 Reminder::find_remind(const String& time) {
    for (u16 i = 0; i < this->max_remind; i++) {
		if (this->remind[i] == time) {
			return i;
		}
    }

    return -1;
}

