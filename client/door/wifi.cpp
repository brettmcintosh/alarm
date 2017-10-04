#include "wifi.h"
#include <ESP8266WiFi.h>
#include <memory>

bool WifiConnection::setup() {
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

bool WifiConnection::is_connected() {
    Serial.println();
    return WiFi.status() ==  WL_CONNECTED;
}

std::unique_ptr<WifiConnection> WifiConnection::create() {
    return std::unique_ptr<WifiConnection> (new WifiConnection());
}
