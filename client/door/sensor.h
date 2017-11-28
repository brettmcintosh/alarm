#include <memory>
#include <Arduino.h>
#include "msg.pb.h"

class Sensor {
    uint8_t pin_number;
    public:
        msg_Update_Service name;
        long read_frequency;
        long last_read;
        String topic;
        Sensor(msg_Update_Service name, String topic_name, uint8_t pin,
            long read_frequency_ms);
        bool time_to_read();
        bool read();
        const char* get_topic();
        static std::unique_ptr<Sensor> create(msg_Update_Service name,
            String topic_name, uint8_t pin, long read_frequency_ms);
};
