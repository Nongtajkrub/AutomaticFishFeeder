#define RUN_PROGRAM

#include <Arduino.h>

#ifdef RUN_PROGRAM

#include "program.hpp"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

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
NTPClient timer(udp, NTP_POOL, NTP_OFFSET); 

const struct Program::Data program_data = {
	// Netpie settings
	.netpie = {
		.MQTT_SERVER = "mqtt.netpie.io",
		.MQTT_CLIENT_ID = "ClientId",
		.MQTT_USERNAME = "Token",
		.MQTT_PASSWORD = "Secret",
		.MQTT_PORT = 1883,
	},
	.feeder = {
		.NTP_CLIENT = &timer,
		.EMPTY_THRESHOLD = 0,
		.DISCHARGE_PER_SESSION = 0,
		.FEEDING_BEFORE_EMPTY = 0,
		.SERVO_DISCHARGE_ANGLE = 0,
		.SERVO_PIN = 0,
		.REFILL_TIME = {0, 0},
		.FEEDING_TIME1 = {0, 0},
		.FEEDING_TIME2 = {0, 0},
		.FEEDING_TIME3 = {0, 0},
		.FEEDING_TIME4 = {0, 0}
	}
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
    Serial.println("Running");
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

#endif // #ifndef RUN_PROGRAM/

