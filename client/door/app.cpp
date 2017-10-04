#include "app.h"

bool App::init() {
    wifi = WifiConnection::create();
    wifi->setup();
    mqtt = MqttConnection::create();
    mqtt->setup();
}

void App::loop() {

}
