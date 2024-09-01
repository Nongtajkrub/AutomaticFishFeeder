#include "type.hpp"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace Netpie {
	class Client {
		private:
			PubSubClient m_client;
			bool m_connected;

		public:
			Client(
				WiFiClient &wifi_client,
				const char* SERVER, 
				const u16   PORT,
				const char* CLIENT_ID,
				const char* USERNAME,
				const char* PASSWORD
				);

		private:
			void connectToNetpie(
				const char* CLIENT_ID,
				const char* USERNAME,
				const char* PASSWORD
				); 
			static void callback(char* topic, byte* payload, uint length);
	};
}
