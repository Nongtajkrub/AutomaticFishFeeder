#include "program.hpp"

#define NTP_POOL "th.pool.ntp.org"
#define NTP_OFFSET 25200

#define MAX_REMIND 32

#define MAX_WIFI_RETRY_CONNECT 10

#define NO_ERRPR 0
#define WIFI_CONNECT_ERROR 1

using namespace Program;

Runner::Runner(const String& wifi_s, const String& wifi_p) {
	this->last_err = NO_ERRPR;
	if (!this->setup_wifi(wifi_s, wifi_p)) { return; }
	this->timer = new NTPTimer(&this->udp, NTP_POOL, NTP_OFFSET);
	this->remind = new Reminder(this->timer, MAX_REMIND, TimeUnit::MINUTE);
}

Runner::~Runner() {
	delete this->timer;
	delete this->remind;
}

u8 Runner::main(u16 loop_delay) {
	this->timer->print(TimeUnit::MINUTE);

	delay(loop_delay);
}

bool Runner::setup_wifi(const String& ssid, const String& pass) {
	u8 retry = 0;
	
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED) {
		if (retry >= MAX_WIFI_RETRY_CONNECT) {
			this->last_err = WIFI_CONNECT_ERROR;
			return false;
		}
		delay(1000);
		retry++;
	}

	return true;
}

u8 Runner::get_last_error() { return this->last_err; }
