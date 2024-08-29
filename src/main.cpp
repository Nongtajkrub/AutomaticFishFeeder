#include "program.hpp"

#define WIFI_SSID "Sunan_2.4G"
#define WIFI_PASS "0871691479"

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

void setup() {
    Serial.begin(9600);
	setup_wifi(WIFI_SSID, WIFI_PASS);
}

void loop() {
	Program::Runner::main();
	delay(1000);
}
