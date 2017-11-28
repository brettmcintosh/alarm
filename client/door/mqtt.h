#include <Arduino.h>
#include <memory>
#include <vector>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "sensor.h"
#include "msg.pb.h"
#include "wifi.h"

class MqttConnection {
    String mqtt_server;
    uint8_t buffer[128];
    size_t msg_length;
    PubSubClient client;
    WiFiClient wifi;
    public:
        MqttConnection(String server_name);
        bool setup();
        void loop();
        bool is_connected();
        void publish(std::vector<Sensor>::iterator& sensor, msg_Update_Status status);
        static std::unique_ptr<MqttConnection> create(String server_name);
};
