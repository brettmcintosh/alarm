import paho.mqtt.client as mqtt_client

import subprocess

from settings import *


class MqttConnection(mqtt_client.Client):

    @classmethod
    def get(cls):
        """Initialize and connect."""
        conn = cls()
        conn.connect(host=MQTT_HOST, port=MQTT_PORT)
        return conn


class MqttMixin:

    def __init__(self, *args, **kwargs):
        super().__init__()
        self.topic = None
        self.msg_q = MqttConnection.get()
        self.msg_q.on_message = self.on_msg
        self.msg_q.loop_start()

    def set_topic(self, topic):
        self.topic = topic
        self.msg_q.subscribe(topic)

    def on_msg(self, client, userdata, msg):
        raise NotImplementedError()

    def send_msg(self, msg):
        self.msg_q.publish(topic=self.topic, payload=msg)

    def update_status(self, status):
        self.send_msg(self.format_msg(status))

    def format_msg(self, *args, **kwargs):
        raise NotImplementedError()


def arping(check_mac=True):
    result = subprocess.run(['arping',
                             '-c', '1',
                             '-w', str(ARPING_TIMEOUT_SECONDS),
                            ARPING_DEVICE_IP],
                            check=True,
                            stdout=subprocess.PIPE)
    if check_mac:
        if bytes(ARPING_DEVICE_MAC.upper(), 'ascii') not in result.stdout:
            raise InvalidMac()


class InvalidMac(Exception):
    pass
