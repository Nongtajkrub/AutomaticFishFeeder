#include "program.hpp"

#define WIFI_SSID "Sunan_2.4G"
#define WIFI_PASSWORD "0871691479"

#define STOP_LOOP() for (;;)

static void setup_wifi(const char* SSID, const char* PASS) {
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
		delay(500);
    }
}

const struct Program::Data program_data = {
	.MQTT_SERVER = "mqtt.netpie.io",
	.MQTT_CLIENT_ID = "383154ff-145e-4508-aaca-30283a119218",
	.MQTT_USERNAME = "ANtvbF27EuP4o1fSjkjV9p3NY7vaJzD2",
	.MQTT_PASSWORD = "MbkYJ1ujNVJdKQxPoiN9SNKdaQcZqXvu",
	.MQTT_PORT = 1883,
};

Program::Runner program_runner(program_data);

void setup() {
    Serial.begin(9600);

	setup_wifi(WIFI_SSID, WIFI_PASSWORD);
	Serial.println("WiFi connected");

	program_runner.setup();
	Serial.println("Netpie connected");
}

void loop() {
	if (program_runner.get_status() != Program::Status::NONE) {
		program_runner.end();
		Serial.println("Something went wrong!");
		STOP_LOOP();
	} else {
		program_runner.loop();
	}
}
