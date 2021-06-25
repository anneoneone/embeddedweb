from app import app
from flask import render_template
from flask import request, redirect
from datetime import datetime
import RPi.GPIO as GPIO

# --- ROUTES ---

@app.route("/")
def index():
    return render_template("public/controlLed.html")


@app.route("/controlLed", methods=["GET", "POST"])
def controlLed():
    if request.method == "POST":
        if (request.is_json):
            payload = request.get_json()
            ledState = payload["ledState"]
            print(ledState)
        else:
            req = request.form

            ledState = req.get("led")


        channel = 20
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(channel, GPIO.OUT)
        GPIO.output(channel, int(ledState))

        return redirect(request.url)

    return render_template(
        "public/controlLed.html"
    )

