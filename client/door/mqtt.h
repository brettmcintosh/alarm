#include <memory>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "sensor.h"
#include "msg.pb.h"
#include "wifi.h"

#define MQTT_SERVER "192.168.44.102"

class MqttConnection {
    const char* mqtt_server;
    uint8_t buffer[128];
    size_t msg_length;
    PubSubClient client;
    WiFiClient wifi;
    public:
        MqttConnection();
        bool setup();
        void loop();
        bool is_connected();
        void publish(std::unique_ptr<Sensor>& sensor, msg_Update_Status status);
        static std::unique_ptr<MqttConnection> create();
};
