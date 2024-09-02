#include "type.hpp"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace Netpie 
{
	enum class ErrorCode : u8 
	{
		NONE,
		CONNECT_FAIL,
		ATTEMPT_SENT_DUPE_DATA,
		DATA_DID_NOT_SEND
	};

	class Client 
	{
		private:
			PubSubClient m_client;
			bool m_connected;
			const char* m_last_payload;

		public:
			Client(WiFiClient &wifi_client, const char* SERVER, const u16 PORT);
			~Client() = default;

		public:
			ErrorCode connect(const char* CLIENT_ID, const char* USERNAME, const char* PASSWORD);
			void disconnect();
			ErrorCode sendData(const char* topic, const char* payload);
			void loop();
		
		private:
			//static void callback(char* topic, byte* payload, uint length);
	};
}
