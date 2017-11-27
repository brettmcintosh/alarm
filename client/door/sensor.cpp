#include "sensor.h"

Sensor::Sensor(msg_Update_Service name, const char* topic, uint8_t pin, int read_frequency) {
    name = name;
    topic = topic;
    pin_number = pin;
    read_frequency_millis = read_frequency;
    pinMode(pin, INPUT);
}

bool Sensor::read() {
    if (digitalRead(pin_number) == HIGH) {
        Serial.println("Input is HIGH!");
        return true;
    }
    return false;
}

std::unique_ptr<Sensor> Sensor::create(msg_Update_Service name, const char* topic,
        uint8_t pin, int read_frequency) {
    return std::unique_ptr<Sensor> {new Sensor(name, topic, pin, read_frequency)};
}
