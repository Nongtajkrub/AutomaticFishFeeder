#include "netpie.hpp"

#include <Arduino.h>

#define MAX_CONNECT_RETRY_COUNT 10

Netpie::Client::Client(WiFiClient &wifi_client, const char* SERVER, const u16 PORT)
	: m_client(wifi_client)
{
	m_client.setServer(SERVER, PORT);
	//m_client.setCallback(callback);
}

Netpie::ErrorCode Netpie::Client::connect(const char* CLIENT_ID, const char* USERNAME, const char* PASSWORD) 
{
	u16 retry_count = 0;

	Serial.println("Trying to connecte to Netpie ");
	while (!m_client.connected())
	{
		if (retry_count >= MAX_CONNECT_RETRY_COUNT)
		{
			Serial.println("Fail to connect with Netpie");
			return ErrorCode::CONNECT_FAIL;
		}

		if (m_client.connect(CLIENT_ID, USERNAME, PASSWORD))
		{
			Serial.println("Connected!");
			return ErrorCode::NONE;
		} 
		else
		{
			Serial.println("Fail to connect with Netpie retrying");
			retry_count++;
			delay(500);
		}
	}

	// should not reach this point but if does assume failer
	return ErrorCode::CONNECT_FAIL;
}

void Netpie::Client::disconnect() { m_client.disconnect(); }

Netpie::ErrorCode Netpie::Client::sendData(const char* topic, const char* payload)
{
	if (payload == m_last_payload) 
	{
		return ErrorCode::ATTEMPT_SENT_DUPE_DATA;
	}
	if (!m_client.publish(topic, payload)) 
	{
		return ErrorCode::DATA_DID_NOT_SEND;
	}

	return ErrorCode::NONE;
}

void Netpie::Client::loop() { m_client.loop(); }

/*
void Netpie::Client::callback(char* topic, byte* payload, uint length) 
{
	Serial.print("Recv message topic - ");
	Serial.println(topic);

	// print the message
	for (uint i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
}
*/
