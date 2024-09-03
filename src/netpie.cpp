#include "netpie.hpp"

#include <Arduino.h>
#include <string.h>

#define MAX_CONNECT_RETRY_COUNT 10

namespace Netpie {
	Client::Client(WiFiClient &wifi_client, const char* SERVER, const u16 PORT)
		: client(wifi_client) 
	{
		this->client.setServer(SERVER, PORT);
			//this->client.setCallback(callback);
	}

	ErrorCode Client::connect(
		const char* CLIENT_ID,
		const char* USERNAME,
		const char* PASSWORD
		) {
		u16 retry_count = 0;

		while (!this->client.connected()) {
			if (retry_count >= MAX_CONNECT_RETRY_COUNT) {
				return ErrorCode::CONNECT_FAIL;
			}
			if (this->client.connect(CLIENT_ID, USERNAME, PASSWORD)) {
				this->connected = true;
				return ErrorCode::NONE;
			}

			retry_count++;
			delay(500);
		}

		// should not reach this point but if does assume failer
		return ErrorCode::CONNECT_FAIL;
	}

	void Client::disconnect() {
		this->client.disconnect(); 
		this->connected = false;
	}

	ErrorCode Client::send_data(const char* topic, const char* payload) {
		if (!this->client.publish(topic, payload))  {
			return ErrorCode::SEND_DATA_FAIL;
		}

		return ErrorCode::NONE;
	}
	
	void Client::loop() { this->client.loop(); }
}

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
