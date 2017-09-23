import subprocess
from time import sleep

from network import arping, MqttMixin
from settings import *


OK = 'ok'
TROUBLE = 'trouble'


class AlarmService(MqttMixin):

    ARMED = 'armed'
    OFF = 'off'
    TRIGGERED = 'triggered'

    def __init__(self):
        super().__init__()
        self.status = self.OFF
        self.set_topic(ALARM_SERVICE_MQTT_TOPIC)

    def arm(self):
        self.status = self.ARMED

    def disarm(self):
        self.status = self.OFF

    def trigger(self):
        self.status = self.TRIGGERED

    def on_msg(self, client, userdata, msg):
        self.consume_msg(msg)

    def consume_msg(self, msg):
        service, status = self.parse_msg(msg)
        print('{} updated its status with {}'.format(service, status))
        if service == ARPING_MQTT_TOPIC:
            if self.check_departure(status):
                print('departed')
                self.arm()
            elif self.check_return(status):
                print('returned')
                self.disarm()
        else:
            if self.check_trigger(status):
                print('triggered')
                self.trigger()

        print('alarm status is {}'.format(self.status))

    def check_departure(self, status):
        return self.status == self.OFF and status == TROUBLE

    def check_return(self, status):
        return self.status == self.ARMED and status == OK

    def check_trigger(self, status):
        return self.status == self.TRIGGERED and status == TROUBLE


class ArpingService(MqttMixin):

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
            self.update_status(TROUBLE)
        else:
            self.update_status(OK)

    def on_msg(self, client, userdata, msg):
        print(msg.payload)
