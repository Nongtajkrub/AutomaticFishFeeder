#include "program.hpp"

#define WIFI_SSID "Sunan_2.4G"
#define WIFI_PASS "0871691479"

/*
static void setup_wifi(const char* ssid, const char* pass) {
    delay(1000);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
    }

    Serial.println("Connected!");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP().toString());
}
*/

Program::Runner runner(WIFI_SSID, WIFI_PASS);

void setup() {
    Serial.begin(9600);

	if (runner.get_last_error() != 0) {
		Serial.print("An error occure code -> ");
		Serial.println(runner.get_last_error());
	}
}

void loop() {
	delay(1000);
}
