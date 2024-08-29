#include "program.hpp"

#define NTP_POOL "th.pool.ntp.org"
#define NTP_OFFSET 25200

#define MAX_REMIND 32

#define MAX_WIFI_RETRY_CONNECT 10

#define NO_ERRPR 0
#define WIFI_CONNECT_ERROR 1

using namespace Program;

u8 Runner::last_err = 0;
WiFiUDP Runner::udp;
Time::NTPTimer Runner::timer(Runner::udp, NTP_POOL, NTP_OFFSET);
Time::Reminder Runner::remind(&Runner::timer, MAX_REMIND, Time::Unit::MINUTE);

void Runner::init_ui() {
	
}

u8 Runner::main() {
	Runner::timer.print(Time::Unit::MINUTE);

	return 0;
}

u8 Runner::get_last_error() { return Runner::last_err; }
