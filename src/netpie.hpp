#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MicroGear.h>

namespace Netpie {
	enum class Event : u8 {
		NONE,
		MESSAGE_RECV
	};

	extern Event event;
	extern String message_recv;

	void handleMessage(char *topic, u8* msg, uint msglen); 
	void handleFoundGear(char *attribute, u8* msg, uint msglen);
	void handleLostGear(char* attribute, u8* msg, uint msglen);
	void handleConnect(char* attribute, u8* msg, uint msglen);

	typedef struct NetpieApi {
		MicroGear microgear;
		bool connected = false;

		NetpieApi(
			WiFiClient wifi_client,
			char* SSID,
			char* PASSWORD,
			char* APPID,
			char* API_KEY,
			char* API_SECRET,
			char* ALIAS
			);
	} netpie_api_t;
}
