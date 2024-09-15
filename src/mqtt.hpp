#include "type.hpp"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace Mqtt {
	enum class ErrorCode : u8 {
		NONE,
		CONNECT_FAIL,
		SEND_DATA_FAIL
	};

	class Client {
	private:
		PubSubClient client;
		bool connected;

	public:
		Client(WiFiClient &wifi_client, const char* SERVER, const u16 PORT);
		~Client() = default;

	public:
		ErrorCode connect(
			const char* CLIENT_ID, 
			const char* USERNAME, 
			const char* PASSWORD
			);
		void disconnect();
		ErrorCode send_data(const char* topic, const char* payload);
		void loop();
	};
}
