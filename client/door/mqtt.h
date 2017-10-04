#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <memory>


#define ALARM_MQTT_TOPIC "alarm/alarm"
#define DOOR_MQTT_TOPIC  "alarm/door"

class MqttConnection {
    const char* mqtt_server;
    PubSubClient client;
    WiFiClient wifi;
    public:
        MqttConnection();
        bool setup();
        bool is_connected();
        void loop();
        static std::unique_ptr<MqttConnection> create();
};
