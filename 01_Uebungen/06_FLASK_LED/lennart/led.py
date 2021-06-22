from flask import Flask, render_template, request

import gpio

app = Flask(__name__)


# Main Page
@app.route("/")
def index():
    return render_template("led.html")


# Route for led handling
@app.route("/led", methods=["POST"])
def switch_leds():
    # Check if the payload is valid json
    if (request.is_json):
        payload = request.get_json()

        # Check wether to turn on or off the specified color
        if "on" == payload["state"]:
            gpio.turn_on(payload["color"])
        elif "off" == payload["state"]:
            gpio.turn_off(payload["color"])

    else:
        print("Error: payload is not json")

    return render_template("led.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0")
