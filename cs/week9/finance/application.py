import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime



from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    index_data = []
    total=0

    data = db.execute("select * from purchases where user_id = " + str(session["user_id"]))
    data2 = db.execute("select * from users where id = " + str(session["user_id"]))

    if len(data) <1:
        index_data.append({
            'symbol': None,
            'name': None,
            'shares': None,
            'price_now': None,
            'price_then': None,
            'total_line': None,
            'total': 10000,
            'price_per_one': None
        })


    for x in range(len(data)):
        y = lookup(data[x]['symbol'])
        w = y['name']
        z = y['price']

        index_data.append({
            'symbol': data[x]['symbol'],
            'name': w,
            'shares': data[x]['shares'],
            'price_now': z*data[x]['shares'],
            'price_then': data[x]['price_per_shares']*data[x]['shares'],
            'total_line': data[x]['shares']*data[x]['price_per_shares'],
            'total': data2[0]['cash'],
            'price_per_one': z
        })

        total+=z*data[x]['shares']
    try:
        total+= index_data[0]['total']
    except:
        pass



    print(index_data)

    return render_template("index.html", data=index_data, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    current_cash= db.execute("select cash from users where id = " + str(session["user_id"]))[0]['cash']

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")


        x=lookup(symbol)
        if x == None:
            return apology("invalid symbol", 400)

        price = int(shares)*x['price']
        new_cash = current_cash - price


        #print("insert into users (cash) values (?)", new_cash + " where id = "+ str(session["user_id"]))

        db.execute("UPDATE users SET cash = "+ str(new_cash) +" WHERE id = "+ str(session["user_id"]) +";")
        db.execute("insert into purchases (user_id, shares, symbol, price_total, price_per_shares) values (?, ?, ?, ?,? )", session["user_id"], shares, symbol, price, x['price'])
        db.execute("insert into history (user_id, type, amount, time, shares, name) values (?,?,?,?,?,?)",str(session["user_id"]), "buy", str(price), str(datetime.now()), str(shares), symbol)
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    data = db.execute("select * from history")
    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    print(session["user_id"])

    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("invalid symbol",400)
        return render_template("quote.html", value=True, data=data)
        return redirect("/")
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    data = db.execute("select username from users")




    if request.method == "POST":


        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirmation")

        passwordHash = generate_password_hash(password)

        if username == "" or password == "" or confirm == "":
            return apology("no input values")

        if password != confirm:
            return apology("your password and confirm are not the same")

        for x in data:
            if x['username'] == username:
                return apology("this username is already used")

        db.execute("insert into users (username, hash) values (?, ?)", username, passwordHash)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    data = db.execute("select * from purchases where user_id = " + str(session["user_id"]))
    data2 = db.execute("select * from users where id = " + str(session["user_id"]))


    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        price_per_stock = lookup(symbol)['price']
        price_before_sell = price_per_stock * int(shares)
        price_finale = data2[0]['cash'] + price_before_sell
        db.execute("UPDATE users SET cash = "+ str(price_finale) +" WHERE id = "+ str(session["user_id"]) +";")
        db.execute("DELETE FROM purchases WHERE user_id = " + str(session["user_id"]) + " and shares = "+ shares + " and symbol = '" + symbol+"'")
        db.execute("insert into history (user_id, type, amount, time, shares, name) values (?,?,?,?,?,?)",str(session["user_id"]), "sell", str(price_before_sell), str(datetime.now()), str(shares), symbol)
        return redirect("/")
    return render_template("sell.html", data=data)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
