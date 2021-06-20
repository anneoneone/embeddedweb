from app import app
from flask import render_template
from flask import request, redirect
from datetime import datetime

# --- FILTERS ---

@app.template_filter("clean_date")
def clean_date(dt):
    return dt.strftime("%d %b %Y")


# --- ESCAPES ---
niceDiv = "<div class='niceDiv'>This is a nice DIV</div>"


# --- ROUTES ---

@app.route("/")
def index():
    return render_template("public/index.html")

@app.route("/about")
def about():
    return render_template("public/index.html")

@app.route("/sign-up", methods=["GET", "POST"])
def sign_up():
    if request.method == "POST":
        # request.form gives access to the sent data
        req = request.form      
        print(req)

        # validate that fields not empty
        missing = list()

        for k, v in req.items():
            if v == "":
                missing.append(k)

        if missing:
            feedback = f"Missing fields for {', '.join(missing)}"
            return render_template("public/sign_up.html", feedback=feedback)

        username = req.get("username")
        email = req.get("email")
        password = req.get("password")

        return redirect(request.url)
    return render_template("public/sign_up.html")

@app.route("/jinja")
def jinja():
    # Strings
    my_name = "Julian"

    # Integers
    my_age = 30

    # Lists
    langs = ["Python", "JavaScript", "Bash", "Ruby", "C", "Rust"]

    # Dictionaries
    friends = {
        "Tony": 43,
        "Cody": 28,
        "Amy": 26,
        "Clarissa": 23,
        "Wendell": 39
    }

    # Tuples
    colors = ("Red", "Blue")

    # Booleans
    cool = True

    # date
    date = datetime.utcnow()

    # Classes
    class GitRemote:
        def __init__(self, name, description, domain):
            self.name = name
            self.description = description 
            self.domain = domain

        def pull(self):
            return f"Pulling repo '{self.name}'"

        def clone(self, repo):
            return f"Cloning into {repo}"

    my_remote = GitRemote(
        name="Learning Flask",
        description="Learn the Flask web framework for Python",
        domain="https://github.com/Julian-Nash/learning-flask.git"
    )

    # Functions
    def repeat(x, qty=1):
        return x * qty

    return render_template(
        "public/jinja.html", 
        my_name=my_name, 
        my_age=my_age, 
        langs=langs,
        friends=friends, 
        colors=colors, 
        cool=cool, 
        GitRemote=GitRemote, 
        my_remote=my_remote, 
        repeat=repeat, 
        date=date,
        niceDiv = niceDiv,
    )