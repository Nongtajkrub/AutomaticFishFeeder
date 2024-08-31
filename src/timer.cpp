#include "timer.hpp"

using namespace Time;

NTPTimer::NTPTimer(WiFiUDP& udp, const char* pool, long offset) :
    NTPClient(udp, pool, offset)
{
	this->begin();
} 

String NTPTimer::time(Unit unit) {
    this->update();

    switch (unit) {
		case Unit::HOUR:
	    	return this->getFormattedTime().substring(0, 2);
		case Unit::MINUTE:
	    	return this->getFormattedTime().substring(0, 5);
		case Unit::SECOND:
		default:
	    	return this->getFormattedTime();
    }
}

void NTPTimer::print(Unit unit) {
    Serial.println(this->time(unit));
}
