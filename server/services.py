import subprocess
from time import sleep

from msg_pb2 import Command, Update
from settings import *

from network import arping, MqttMixin


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
        self.arm_door()

    def arm_door(self):
        cmd = Command()
        cmd.command = cmd.ARM
        self.send_command(cmd, 'door')

    def disarm_door(self):
        cmd = Command()
        cmd.command = cmd.DISARM
        self.send_command(cmd, 'door')

    def disarm(self):
        self.status = self.OFF
        self.disarm_door()

    def trigger(self):
        self.status = self.TRIGGERED

    def on_msg(self, client, userdata, msg):
        self.consume_update(self.parse_update(msg))

    def consume_update(self, update):
        if update.service_name == update.ARPING:
            if self.check_departure(update):
                print('departed')
                self.arm()
            elif self.check_return(update):
                print('returned')
                self.disarm()
        else:
            print('update {}'.format(update))
            if self.check_trigger(update):
                print('triggered')
                self.trigger()

        print('alarm status is {}'.format(self.status))

    def check_departure(self, update):
        return self.status == self.OFF and update.status == Update.TROUBLE

    def check_return(self, update):
        return self.status == self.ARMED and update.status == Update.OK

    def check_trigger(self, update):
        return self.status == self.ARMED and update.status == Update.TROUBLE


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
        update = Update()
        update.service_name = update.ARPING
        try:
            arping(check_mac=True)
        except subprocess.CalledProcessError:
            update.status = update.TROUBLE
        else:
            update.status = update.OK
        self.update_status(update)

    def on_msg(self, client, userdata, msg):
        print(msg.payload)
