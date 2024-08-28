#include "timer.hpp"

NTPTimer::NTPTimer(WiFiUDP& udp, const char* pool, long off) :
    NTPClient(udp, pool, off)
{
	this->begin();
} 

String NTPTimer::time(TimeUnit unit) {
    this->update();

    switch (unit) {
		case TimeUnit::HOUR:
	    	return this->getFormattedTime().substring(0, 2);
		case TimeUnit::MINUTE:
	    	return this->getFormattedTime().substring(0, 5);
		case TimeUnit::SECOND:
		default:
	    	return this->getFormattedTime();
    }
}

void NTPTimer::print(TimeUnit unit) {
    Serial.println(this->time(unit));
}
