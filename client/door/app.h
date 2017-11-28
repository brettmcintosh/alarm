#include <memory>
#include <vector>
#include "mqtt.h"
#include "msg.pb.h"

class App {
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unique_ptr<WifiConnection> wifi;
    public:
        std::unique_ptr<MqttConnection> mqtt;
        bool init();
        void loop();
        void add_sensor(msg_Update_Service name, String topic,
            uint8_t pin, long read_frequency_ms);
};
