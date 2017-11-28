#include <stdio.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "msg.pb.h"
#include "app.h"

#define PIR_PIN 14
#define DOOR_PIN 12
#define PIR_SCAN_FREQUENCY_MS 2000
#define DOOR_SCAN_FREQUENCY_MS 1000
#define PIR_TOPIC "alarm/pir"
#define DOOR_TOPIC "alarm/door"
#define MQTT_SERVER "192.168.44.175"

std::unique_ptr<App> app;

void setup() {
    Serial.begin(115200);

    app = std::unique_ptr<App>(new App);
    app->init(MQTT_SERVER);
    Serial.println("App initialized");

    Serial.println(PIR_TOPIC);
    app->add_sensor(msg_Update_Service_PIR, PIR_TOPIC,
        PIR_PIN, PIR_SCAN_FREQUENCY_MS);
//    app->add_sensor(msg_Update_Service_DOOR, DOOR_TOPIC,
//        DOOR_PIN, DOOR_SCAN_FREQUENCY_MS);

    Serial.println("Sensors up");
}

void loop() {
    app->loop();
}
