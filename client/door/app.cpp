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
        Serial.println("Reading sensor: " + (*s)->name);
        if ((*s)->read()) {
            mqtt->publish(*s, msg_Update_Status_TROUBLE);
        }
        else {
            mqtt->publish(*s, msg_Update_Status_OK);
        }
    }
}


void App::add_sensor(msg_Update_Service name, const char* topic,
        uint8_t pin, int read_frequency) {
    sensors.push_back(Sensor::create(name, topic, pin, read_frequency));
}
