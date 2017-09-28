#include <stdio.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "msg.pb.h"

#define PIR_PIN 14
#define DOOR_PIN 12

#define ALARM_MQTT_TOPIC "alarm/alarm"
#define DOOR_MQTT_TOPIC "alarm/door"
#define SERVICE_NAME msg_Update_Service_DOOR
#define PIR_SCAN_FREQUENCY_MS 2000
#define DOOR_SCAN_FREQUENCY_MS 1000
#define OK_UPDATE_FREQUENCY_MS 15000

const char* ssid = "Mojave";
const char* password = "2856d18b84c94ab1b1e3";
const char* mqtt_server = "192.168.44.144";

WiFiClient espClient;
PubSubClient client(espClient);
long next_pir_scan_ms = 0;
long next_door_scan_ms = 0;
long next_pir_ok_update_ms = 0;
long next_door_ok_update_ms = 0;
char msg[50];

uint8_t buffer[128];
size_t msg_length;

bool armed;
bool triggered;

void setup_wifi() {
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "DOOR";
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            client.subscribe(DOOR_MQTT_TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void on_msg(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    parse_command(payload, length);
}

void setup() {
    pinMode(PIR_PIN, INPUT);
    pinMode(DOOR_PIN, INPUT);
    Serial.begin(115200);

    client.setServer(mqtt_server, 1883);
    client.setCallback(on_msg);
    setup_wifi();

    armed = false;
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    if (armed && !triggered) {
        if (millis() >= next_pir_scan_ms) {
            scan_pir();
        }
//        if (millis() >= next_door_scan_ms) {
//            scan_door();
//        }
    }
}

void scan_pir() {
    if (digitalRead(PIR_PIN) == HIGH) {
        Serial.println("PIR TROUBLE");
        send_update(ALARM_MQTT_TOPIC, msg_Update_Status_TROUBLE);
        trigger();
    }
    else {
        Serial.println("PIR OK");
        if (millis() >= next_pir_ok_update_ms) {
            send_update(ALARM_MQTT_TOPIC, msg_Update_Status_OK);
            next_pir_ok_update_ms = millis() + OK_UPDATE_FREQUENCY_MS;
        }
    }
    next_pir_scan_ms = millis() + PIR_SCAN_FREQUENCY_MS;
}

void scan_door() {
    if (digitalRead(DOOR_PIN) == HIGH) {
        Serial.println("DOOR TROUBLE");
        send_update(ALARM_MQTT_TOPIC, msg_Update_Status_TROUBLE);
        trigger();
    }
    else {
        Serial.println("DOOR OK");
        if (millis() > next_door_ok_update_ms) {
            send_update(ALARM_MQTT_TOPIC, msg_Update_Status_OK);
            next_door_ok_update_ms = millis() + OK_UPDATE_FREQUENCY_MS;
        }
    }
    next_door_scan_ms = millis() + PIR_SCAN_FREQUENCY_MS;
}

void send_update(char* topic, msg_Update_Status update_status) {
    msg_Update update = msg_Update_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    update.service_name = SERVICE_NAME;
    update.status = update_status;

    if (!pb_encode(&stream, msg_Update_fields, &update)) {
        Serial.println("encoding failed");
        Serial.println(PB_GET_ERROR(&stream));
    }
    else {
        if (!client.publish(topic, buffer, stream.bytes_written)) {
            Serial.println("Failed to publish buffer to topic");
        }
        else {
            Serial.print("Sent msg with length ");
            Serial.println(stream.bytes_written);
        }
    }
}

void parse_command(byte* command_buf, unsigned int length) {
    msg_Command command = msg_Command_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(buffer, length);
    if (!pb_decode(&stream, msg_Command_fields, &command)) {
        Serial.println("decoding failed");
    }
    else {
        if (command.command == msg_Command_Do_ARM) {
            arm();
            Serial.println("armed");
            send_update(ALARM_MQTT_TOPIC, msg_Update_Status_ARMED);
        }
        else if (command.command == msg_Command_Do_DISARM) {
            disarm();
            Serial.println("disarmed");
            send_update(ALARM_MQTT_TOPIC, msg_Update_Status_DISARMED);
        }
    }
}

void arm() {
    armed = true;
    triggered = false;
}

void disarm() {
    armed = false;
    triggered = false;
}

void trigger() {
    if (armed) {
        triggered = true;
    }
}
