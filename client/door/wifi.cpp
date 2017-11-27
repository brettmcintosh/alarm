#include "wifi.h"
#include <ESP8266WiFi.h>
#include <memory>

bool WifiConnection::setup() {
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(kSSID);
    WiFi.begin(kSSID, kPASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void WifiConnection::loop() {
    if (!is_connected()) {
        Serial.println("Lost connection.  Trying to reconnect...");
        setup();
    }
}

bool WifiConnection::is_connected() {
    return WiFi.status() ==  WL_CONNECTED;
}

std::unique_ptr<WifiConnection> WifiConnection::create() {
    return std::unique_ptr<WifiConnection> (new WifiConnection());
}
