"""
    Flask project with user authentication.
    Only authenticated users, are allowed to switch LED's on/off.

    Sources:
        https://techmonger.github.io/10/flask-simple-authentication/
        https://github.com/techmonger/flask-simple-login

"""

from flask import Flask, render_template, request, flash, redirect, url_for, session, abort
from flask_sqlalchemy import sqlalchemy, SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

import gpio

app = Flask(__name__)
app.config["SECRET_KEY"] = "$a634bjd(&34nnmsdf}][#y"

# Database configuration
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///auth.db"
db = SQLAlchemy(app)

class User(db.Model):
    userid    = db.Column(db.Integer, primary_key=True)
    username  = db.Column(db.String(100), unique=True, nullable=False)
    pass_hash = db.Column(db.String(100), nullable=False)

    def __repr__(self):
        return '' % self.username


def create_db():
    """ 
    Create database.
    
    Only run once to create an empty database in the current directory.
    """
    db.create_all()


# Landing page
@app.route("/")
def index():
    return redirect(url_for("login"))


# Route for led handling
@app.route("/led", methods=["GET", "POST"])
def led():

    # Check if logged in
    if not session.get("loggedIn"):
        return redirect(url_for("login"))
    
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


# Login route
@app.route("/login", methods=["GET", "POST"])
def login():
    if "POST" == request.method:

        # Get username and password from form
        username = request.form["username"]
        password = request.form["password"]

        # Check if fields are filled
        if not (username and password):
            flash("Please fill every field.", "warning")
            return redirect(url_for("login"))
        else:
            username = username.strip()
            password = password.strip()

        # Get the user from the database
        user = User.query.filter_by(username=username).first()

        # Check if user exists and password matches
        if user and check_password_hash(user.pass_hash, password):
            session["username"] = username
            session["loggedIn"] = True
            return redirect(url_for("led"))
        else:
            flash("Username or password are invalid.", "error")


    return render_template("login.html")


# Signup route
@app.route("/signup", methods=["GET", "POST"])
def signup():
    if "POST" == request.method:
        
        # Get username and password from the form
        username = request.form["username"]
        password = request.form["password"]

        # Check if something not left empty 
        if not (username and password):
            flash("Please fill every field.", "warning")
            return redirect(url_for("signup"))
        else:
            username = username.strip()
            password = password.strip()

        # Create pw hash
        pw_hash = generate_password_hash(password, "sha256")

        # Create new user
        new_user = User(username=username, pass_hash=pw_hash)

        # Save new user
        db.session.add(new_user)

        # Try to push the new user to the database
        # If the username already exist we get a IntegrityError
        try:
            db.session.commit()
        except sqlalchemy.exc.IntegrityError:
            flash(f"Username {username} is not available.", "error")
            return redirect(url_for("signup"))

        flash("Account created succesfully", "success")
        return redirect(url_for("login"))

    return render_template("signup.html")


# Logout route
@app.route("/logout", methods=["GET"])
def logout():
    session.pop("loggedIn", None)
    session.pop("username", None)
    return redirect(url_for("login"))


if __name__ == "__main__":
    app.run(host="0.0.0.0")
