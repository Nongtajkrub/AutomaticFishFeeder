#include "timer.hpp"

namespace Time {
	NTPTimer::NTPTimer(WiFiUDP& udp, const char* pool, long offset) :
		NTPClient(udp, pool, offset)
	{
		begin();
	} 

	String NTPTimer::time(Unit unit) {
		update();

		switch (unit) {
			case Unit::HOUR:
				return getFormattedTime().substring(0, 2);
			case Unit::MINUTE:
				return getFormattedTime().substring(0, 5);
			case Unit::SECOND:
			default:
				return getFormattedTime();
		}
	}

	void NTPTimer::print(Unit unit) {
		Serial.println(time(unit));
	}
}
