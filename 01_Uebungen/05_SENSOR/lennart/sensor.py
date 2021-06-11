#!/usr/bin/python3
"""
    CGI script reading temperature and humidity from a DHT11 sensor.
    Response is formatted as JSON like this:
    {
        "temp": 23.0,
        "hum" : 33.0
    }
"""

import Adafruit_DHT, json

SENSOR_PIN = 4

def get_environment_values():
    """ Read the values from dht11 and return the tuple. """
    hum, temp = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, SENSOR_PIN)
    return (hum, temp)


def values_to_json(hum, temp):
    """ Convert the values to a JSON representation. """
    env = {"temp": temp, "hum": hum}
    return json.dumps(env)


# Main program starts here
vals = get_environment_values()
print("Content-type: text/json\n")
print(values_to_json(*vals))
