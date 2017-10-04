#include "mqtt.h"
#include "wifi.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <memory>

MqttConnection::MqttConnection() {
    client = PubSubClient(wifi);
}

bool MqttConnection::setup() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "DOOR";
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            client.subscribe(DOOR_MQTT_TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

bool MqttConnection::is_connected() {
    Serial.println();
    return WiFi.status() ==  WL_CONNECTED;
}

std::unique_ptr<MqttConnection> MqttConnection::create() {
    return std::unique_ptr<MqttConnection> (new MqttConnection());
}