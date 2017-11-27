#include <memory>
#include <Arduino.h>
#include "msg.pb.h"

class Sensor {
    uint8_t pin_number;
    int read_frequency_millis;

    public:
        msg_Update_Service name;
        const char* topic;
        Sensor(msg_Update_Service name, const char* topic, uint8_t pin,
            int read_frequency);
        long next_read_millis;
        bool read();
        static std::unique_ptr<Sensor> create(msg_Update_Service name, const char* topic,
            uint8_t pin, int read_frequency);
};
