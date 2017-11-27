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

long next_pir_scan_ms = 0;
long next_door_scan_ms = 0;
long next_pir_ok_update_ms = 0;
long next_door_ok_update_ms = 0;

std::unique_ptr<App> app;

void setup() {
    Serial.begin(115200);

    app = std::unique_ptr<App>(new App);
    app->init();
    Serial.println("App initialized");

    app->add_sensor(msg_Update_Service_PIR, "alarm/pir",
        PIR_PIN, PIR_SCAN_FREQUENCY_MS);
    app->add_sensor(msg_Update_Service_DOOR, "alarm/door",
        DOOR_PIN, DOOR_SCAN_FREQUENCY_MS);

    Serial.println("Sensors up");
}

void loop() {
    app->loop();
}
