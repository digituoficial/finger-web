#!/usr/bin/env python3

import paho.mqtt.publish as pub
import paho.mqtt.client as mqtt
import datetime


def initialize(client, userdata, flags, rc):
    time = datetime.datetime.now()
    print("code: {} --- {}/{}/{} ".format(rc, time.day, time.month, time.year))
    client.subscribe("fingerprint/receive")
    client.subscribe("fingerprint/confirm")


def send_message(msg, topic, port=1883, server=''):
    if msg and topic and server:
        pub.single(topic, payload=msg, port=port, hostname=server)
        return True
    return False


def message(client, userdata, msg):
    if msg.topic == 'fingerprint/receive':
        if msg.payload.decode('utf-8') == 'conhecida':
            send_message("Abra a porta",
                         topic='fingerprint/confirm', server='localhost')
        else:
            send_message("A porta deve continuar fechada",
                         topic='fingerprint/confirm', server='localhost')
    elif msg.topic == 'fingerprint/confirm':
        pass


if __name__ == '__main__':
    client = mqtt.Client()
    client.connect("localhost", 1883)
    client.on_connect = initialize
    client.on_message = message
    client.loop_forever()
