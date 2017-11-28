#include "app.h"

bool App::init() {
    wifi = WifiConnection::create();
    wifi->setup();
    mqtt = MqttConnection::create();
    mqtt->setup();
}

void App::loop() {
    wifi->loop();
    mqtt->loop();
    for (std::vector<std::unique_ptr<Sensor>>::iterator s = sensors.begin();
            s != sensors.end(); ++s) {
        if ((*s)->time_to_read()) {
            if ((*s)->read()) {
                mqtt->publish(*s, msg_Update_Status_TROUBLE);
            }
            else {
                mqtt->publish(*s, msg_Update_Status_OK);
            }
        }
    }
}


void App::add_sensor(msg_Update_Service name, String topic,
        uint8_t pin, long read_frequency_ms) {
    sensors.push_back(Sensor::create(name, topic, pin, read_frequency_ms));
}
