#include "program.hpp"

#define NTP_POOL "th.pool.ntp.org"
#define NTP_OFFSET 25200

#define MAX_REMIND 32

#define MAX_WIFI_RETRY_CONNECT 10

#define NO_ERRPR 0
#define WIFI_CONNECT_ERROR 1

u8 Program::Runner::m_last_error = 0;
WiFiUDP Program::Runner::m_udp;
Time::NTPTimer Program::Runner::m_timer(m_udp, NTP_POOL, NTP_OFFSET);
Time::Reminder Program::Runner::m_reminder(&m_timer, MAX_REMIND, Time::Unit::MINUTE);

void Program::Runner::initUi() {
	
}

u8 Program::Runner::main() {
	m_timer.print(Time::Unit::MINUTE);

	return 0;
}

u8 Program::Runner::getLastError() { return m_last_error; }
