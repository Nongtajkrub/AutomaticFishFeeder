#include "netpie.hpp"

using namespace Netpie;

NetpieApi::NetpieApi(
	WiFiClient wifi_client,
	char* SSID,
	char* PASSWORD,
	char* APPID,
	char* API_KEY,
	char* API_SECRET,
	char* ALIAS
	) :
	microgear(wifi_client)
{
	// when new message
	microgear.on(MESSAGE, handleMessage);
	// when found new gear
	microgear.on(PRESENT, handleFoundGear);
	// when loss gear
	microgear.on(ABSENT, handleLostGear);
	// wehn connect to netpie
	microgear.on(CONNECTED, handleConnect);

	microgear.init(API_KEY, API_SECRET, ALIAS);
	microgear.connect(APPID);

	while (!microgear.connected()) {
		delay(1000);
		Serial.println("Connecting to Netpie");
	}
	Serial.println("Connected!");
	this->connected = true;
}

Event Netpie::event = Event::NONE;
String Netpie::message_recv = "";

void handleMessage(char *topic, u8* msg, uint msglen) {
	msg[msglen] = '\0';
	Netpie::message_recv = String((char*)msg);
}
