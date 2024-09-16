#include "timer.hpp"

namespace Time {
	Timer::Timer(WiFiUDP& udp, const char* pool, long offset) :
		NTPClient(udp, pool, offset)
	{
		begin();
	} 

	String Timer::string_time(Unit unit) {
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

	void Timer::print(Unit unit) {
		update();
	}
}
