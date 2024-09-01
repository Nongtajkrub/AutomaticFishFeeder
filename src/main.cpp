#include "program.hpp"

// have to be done like this for Netpie to work. I hate it to
char WIFI_SSID[40] = "Sunan_2.4G";
char WIFI_PASS[40] = "0871691479";
char NETPIE_APPID[40] = "P238758401044";
char NETPIE_KEY[40] = "383154ff-145e-4508-aaca-30283a119218";
char NETPIE_SECRET[40] = "MbkYJ1ujNVJdKQxPoiN9SNKdaQcZqXvu";
char NETPIE_ALIAS[40] = "esp8266";

static void setupWifi(const char* ssid, const char* pass) {
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
	setupWifi(WIFI_SSID, WIFI_PASS);
}

void loop() {
	delay(1000);
}
