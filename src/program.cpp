#include "program.hpp"

#define LOOP_DELAY 500

//#define NTP_POOL "th.pool.ntp.org"
//#define NTP_OFFSET 25200

Program::Runner::Runner(const struct Program::Data& data) :
	m_data(data),
	m_netpie(data.wifi_client, data.MQTT_SERVER, data.MQTT_PORT)
{}

bool Program::Runner::setup()
{
	m_netpie.connect(m_data.CLIENT_ID, m_data.USERNAME, m_data.PASSWORD);
}

bool Program::Runner::loop()
{
	m_netpie.loop();

	delay(LOOP_DELAY);
}
