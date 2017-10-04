#include "mqtt.h"
#include "wifi.h"
#include <memory>

class App {
    std::unique_ptr<WifiConnection> wifi;
    std::unique_ptr<MqttConnection> mqtt;
    public:
        bool init();
        void loop();
};
