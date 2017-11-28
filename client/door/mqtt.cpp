#include "mqtt.h"

MqttConnection::MqttConnection() {
    client = PubSubClient(wifi);
}

bool MqttConnection::setup() {
    client.setServer(MQTT_SERVER, 1883);
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = "DOOR";
        if (client.connect(clientId.c_str())) {
            Serial.println("Connected");
        } else {
            Serial.print("Failed with error: ");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void MqttConnection::loop() {
    if (!is_connected()) {
        Serial.println("Running reconnect");
        setup();
    }
    client.loop();
}

bool MqttConnection::is_connected() {
    return client.connected();
}

void MqttConnection::publish(std::vector<Sensor>::iterator& sensor, msg_Update_Status status) {
    msg_Update update = msg_Update_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    update.service_name = sensor->name;
    update.status = status;

    if (!pb_encode(&stream, msg_Update_fields, &update)) {
        Serial.println("encoding failed");
        Serial.println(PB_GET_ERROR(&stream));
    }
    else {
        if (!client.publish(sensor->get_topic(), buffer, stream.bytes_written)) {
            Serial.println("Failed to publish buffer to topic");
        }
        else {
            Serial.print("Sent msg with length ");
            Serial.println(stream.bytes_written);
        }
    }
}

std::unique_ptr<MqttConnection> MqttConnection::create() {
    return std::unique_ptr<MqttConnection> (new MqttConnection());
}