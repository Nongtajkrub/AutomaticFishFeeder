#define RUN_PROGRAM

#include <Arduino.h>

#ifdef RUN_PROGRAM

#include "program.hpp"
#include <ESP8266WiFi.h>

#define WIFI_SSID "Sunan_2.4G"
#define WIFI_PASSWORD "0871691479"
#define NTP_POOL "th.pool.ntp.org"
#define NTP_OFFSET 25200

#define STOP_LOOP() for (;;)

static void setup_wifi(const char* SSID, const char* PASS) {
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
		Serial.println("Connecting to Wifi");
		delay(500);
    }
}

WiFiUDP udp;
Time::Timer timer(udp, NTP_POOL, NTP_OFFSET);

const struct Program::Data program_data = {
	.MQTT_SERVER = "mqtt.netpie.io",
	.MQTT_CLIENT_ID = "383154ff-145e-4508-aaca-30283a119218",
	.MQTT_USERNAME = "ANtvbF27EuP4o1fSjkjV9p3NY7vaJzD2",
	.MQTT_PASSWORD = "MbkYJ1ujNVJdKQxPoiN9SNKdaQcZqXvu",
	.MQTT_PORT = 1883,
	.EMPTY_THRESHOLD = 20,
	.DISCHARGE_PER_SESSION = 3,
	.FEEDING_BEFORE_EMPTY = 10,
	.SERVO_DISCHARGE_ANGLE = 90,
	.SERVO_PIN = 13,
	.TIMER = &timer,
	.FEEDING_TIME1 = "19:03",
	.FEEDING_TIME2 = "19:05",
	.FEEDING_TIME3 = "19:07",
	.FEEDING_TIME4 = NULL,
	.FEEDING_TIME5 = NULL
};

Program::Runner program_runner(program_data);

void setup() {
    Serial.begin(9600);

	setup_wifi(WIFI_SSID, WIFI_PASSWORD);
	Serial.println("WiFi connected");

	program_runner.setup();
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

#endif // #ifdef RUN_PROGRAM

#ifndef RUN_PROGRAM

void setup() {

}

void loop() {
	delay(1000);	
}

#endif // #ifndef RUN_PROGRAM
