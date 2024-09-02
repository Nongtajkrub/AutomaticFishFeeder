//#include "program.hpp"

#include "WiFiClient.h"
#include "netpie.hpp"

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "Sunan_2.4G"
#define WIFI_PASSWORD "0871691479"

#define MQTT_SERVER "mqtt.netpie.io"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "383154ff-145e-4508-aaca-30283a119218"
#define MQTT_USERNAME "ANtvbF27EuP4o1fSjkjV9p3NY7vaJzD2"
#define MQTT_PASSWORD "MbkYJ1ujNVJdKQxPoiN9SNKdaQcZqXvu"

static void setupWifi(const char* ssid, const char* pass) 
{
    delay(500);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(".");
    }

    Serial.println("Connected to WiFi!");
}

WiFiClient wifi_client;
Netpie::Client netpie_client(wifi_client, MQTT_SERVER, MQTT_PORT);

void setup() 
{
    Serial.begin(9600);
	setupWifi(WIFI_SSID, WIFI_PASSWORD);
	netpie_client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
}

bool disconnected = false;

void loop() 
{
	delay(1000);
	netpie_client.loop();
	if (!disconnected)
	{
		netpie_client.disconnect();
		disconnected = true;
	}
}
