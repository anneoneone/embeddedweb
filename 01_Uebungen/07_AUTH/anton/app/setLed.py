#!/usr/bin/python3

import RPi.GPIO as GPIO

def setValueToLed():

    print("hello")
    GPIO.setmode(GPIO.BCM)
    channel = 20
    GPIO.setup(channel, GPIO.OUT)
    GPIO.output(channel, state)
    GPIO.cleanup()
    return 0

print("hello")

