#include "netpie.hpp"
#include "core_esp8266_features.h"

#include <Arduino.h>

// cant use "using namespace Netpie"

Netpie::Client::Client(
	WiFiClient &wifi_client,
	const char* SERVER, 
	const u16   PORT,
	const char* CLIENT_ID,
	const char* USERNAME,
	const char* PASSWORD
)
	: m_client(wifi_client)
{
	m_client.setServer(SERVER, PORT);
	m_client.setCallback(callback);
	connectToNetpie(CLIENT_ID, USERNAME, PASSWORD);
}

void Netpie::Client::connectToNetpie(
	const char* CLIENT_ID,
	const char* USERNAME,
	const char* PASSWORD
	) 
{
	Serial.println("Trying to connecte to Netpie ");
	while (!m_client.connected())
	{
		if (m_client.connect(CLIENT_ID, USERNAME, PASSWORD))
		{
			Serial.println("Connected!");
		} 
		else
		{
			Serial.println("Fail to connect with Netpie");
			delay(1000);
		}
	}
}

void Netpie::Client::callback(char* topic, byte* payload, uint length) 
{

}
