#include "sensor.h"

Sensor::Sensor(msg_Update_Service name, String topic_name, uint8_t pin,
        long read_frequency_ms) {
    name = name;
    topic = topic_name;
    pin_number = pin;
    read_frequency = read_frequency_ms;
    last_read = millis();
    pinMode(pin, INPUT);
}

bool Sensor::time_to_read() {
    return millis() - last_read >= read_frequency;
}

bool Sensor::read() {
    last_read = millis();
    if (digitalRead(pin_number) == HIGH) {
        Serial.println("Input is HIGH!");
        return true;
    }
    return false;
}

const char* Sensor::get_topic() {
    Serial.println(topic);
    return topic.c_str();
}

std::unique_ptr<Sensor> Sensor::create(msg_Update_Service name, String topic,
        uint8_t pin, long read_frequency_ms) {
    return std::unique_ptr<Sensor> {new Sensor(name, topic, pin, read_frequency_ms)};
}
