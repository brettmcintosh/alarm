import subprocess
from time import sleep

from network import arping, MqttMixin
from settings import *


class AlarmService(MqttMixin):

    ARMED = 'armed'
    OFF = 'off'
    TRIGGERED = 'triggered'

    def __init__(self):
        super().__init__()
        self.state = self.OFF

    def arm(self):
        pass

    def disarm(self):
        pass

    def trigger(self):
        pass

    def format_msg(self, data):
        return 'responding : {}'.format(data)

    def on_msg(self, client, userdata, msg):
        print(msg.payload)


class ArpingService(MqttMixin):

    RESPONDING = True

    def __init__(self):
        super().__init__()
        self.is_active = False
        self.set_topic(ARPING_MQTT_TOPIC)

    def start(self):
        self.is_active = True
        while self.is_active:
            self.ping_device()
            sleep(ARPING_FREQUENCY_SECONDS)

    def ping_device(self):
        try:
            arping(check_mac=True)
        except subprocess.CalledProcessError:
            self.update_status(not self.RESPONDING)
        else:
            self.update_status(self.RESPONDING)

    def format_msg(self, data):
        return 'responding : {}'.format(data)

    def on_msg(self, client, userdata, msg):
        print(msg.payload)
