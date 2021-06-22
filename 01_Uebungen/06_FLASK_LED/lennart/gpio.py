from gpiozero import LED

# We have a red led connected to GPIO 16
#   and a green led connected to GPIO 20

led_red = LED(16)
led_grn = LED(20)


def turn_on(color):
    """
    Color can be "red" or "green"
    """
    if "red" == color:
        led_red.on()
    elif "green" == color:
        led_grn.on()

def turn_off(color):
    """
    Color can be "red" or "green"
    """
    if "red" == color:
        led_red.off()
    elif "green" == color:
        led_grn.off()
