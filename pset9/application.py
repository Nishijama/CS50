import os
from decimal import Decimal
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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
    user = session["user_id"]
    SUBGRANDtotal = 0

    # update currentPrice and total
    x = db.execute("SELECT symbol FROM main WHERE user=?", user)
    for i in range(len(x)):
        symbol = x[i].get("symbol")
        search = lookup(symbol)
        currentPrice = float(search["price"])
        currentPrice = round(currentPrice, 2)
        db.execute("UPDATE main SET currentPrice = ? WHERE user=? AND symbol=?", currentPrice, user, symbol)

        y = db.execute("SELECT shares FROM main WHERE user=? and symbol=?", user, symbol)
        for i in range(len(y)):
            shares = y[i].get("shares")
            total = float(shares * currentPrice)
            total = round(total, 2)
            db.execute("UPDATE main SET total = ? WHERE user=? AND symbol=?", total, user, symbol)
            SUBGRANDtotal = SUBGRANDtotal + total

    # update GRANDtotal
    z = db.execute("SELECT cash FROM users WHERE id=?", user)
    for i in range(len(z)):
        cash = float(z[i].get("cash"))
    GRANDtotal = round(SUBGRANDtotal + cash, 2)
    db.execute("UPDATE users SET GRANDtotal =? WHERE id=?", GRANDtotal, user)

    rows = db.execute("SELECT * FROM main WHERE user=?", user)
    rows2 = db.execute("SELECT cash FROM users WHERE id=?", user)
    rows3 = db.execute("SELECT GRANDtotal FROM users WHERE id=?", user)
    return render_template("index.html", rows=rows, rows2=rows2, rows3=rows3)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        search = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        try:
            int(shares)
        except ValueError:
            return apology("Integer!", 400)
        shares = float(shares)
        if search == None:
            return apology("wrong symbol", 400)
        if request.form.get("shares") == "":
            return apology("Please insert number of shares", 400)
        if float(request.form.get("shares")) <= 0:
            return apology("Number of shares needs to be a positive integer", 400)
        else:
            name = search["name"]
            price = float(search["price"])
            price = round(price, 2)
            symbol = search["symbol"]
            user = session["user_id"]
            total = price * shares
            print(total)
            x = db.execute("SELECT cash FROM users WHERE id=?", user)
            for i in range(len(x)):
                cash = round(x[i].get("cash"), 2)

            if total < cash:
                # update users table
                cash = round(cash - price*shares, 2)
                db.execute("UPDATE users SET cash =? WHERE id=?", cash, user)

                # update history table
                # time code from https://www.programiz.com/python-programming/datetime/current-time
                now = datetime.now()
                transactionTime = now.strftime("%Y-%m-%d %H:%M:%S")
                print(transactionTime)
                db.execute("INSERT INTO history (symbol, shares, price, time, user) VALUES (:symbol, :shares, :price, :time, :user)",
                           symbol=symbol, shares=shares, price=price, time=transactionTime, user=user)

                # update main table
                rows = db.execute("SELECT * FROM main WHERE symbol=? AND user=?", symbol, user)
                if len(rows) == 0:
                    db.execute("INSERT INTO main (symbol, name, shares, price, total, user) VALUES (:symbol, :name, :shares, :price, :total, :user)",
                               symbol=symbol, name=name, shares=shares, price=price, total=total, user=user)
                else:
                    x = db.execute("SELECT shares FROM main WHERE user=? AND symbol=?", user, symbol)
                    for i in range(len(x)):
                        ORIGINALshares = x[i].get("shares")
                        print(ORIGINALshares)
                        TOTALshares = ORIGINALshares + shares
                        db.execute("UPDATE main SET shares =? WHERE user=? AND symbol=?", TOTALshares, user, symbol)

                        y = db.execute("SELECT total FROM main WHERE user=? AND symbol=?", user, symbol)
                        for i in range(len(y)):
                            ORIGINALtotal = y[i].get("total")
                            print(ORIGINALtotal)
                            TOTALtotal = float(ORIGINALtotal) + float(total)
                            TOTALtotal = TOTALshares*price
                        db.execute("UPDATE main SET total =? WHERE user=? AND symbol=?", TOTALtotal, user, symbol)
                return redirect("/")
            else:
                return apology("not enough cash to buy", 400)


@app.route("/history")
@login_required
def history():
    user = session["user_id"]
    rows = db.execute("SELECT * FROM history WHERE user=?", user)
    return render_template("history.html", rows=rows)


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        search = lookup(request.form.get("symbol"))
        if search == None:
            return apology("wrong symbol", 400)
        else:
            return render_template("quoted.html",   name=search["name"],
                                   price=search["price"],
                                   symbol=search["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if password == "":
            return apology("Please provide a password")
        if username == "":
            return apology("Please provide a username")
        if password != confirmation:
            return apology("Your passwords didn't match")

        existingUsers = db.execute("SELECT username FROM users")
        for row in range(len(existingUsers)):
            if existingUsers[row].get("username") == username:
                return apology("Sorry, this username is taken")

        pwhash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :pwhash)", username=username, pwhash=pwhash)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user = session["user_id"]
    if request.method == "GET":
        rows = db.execute("SELECT symbol FROM main WHERE user=?", user)
        return render_template("sell.html", rows=rows)
    else:
        # if blockers
        if request.form.get("shares") == "":
            return apology("Please insert number of shares")
        if float(request.form.get("shares")) <= 0:
            return apology("Number of shares needs to be a positive integer")
        else:
            symbol = request.form.get("symbol")
            print(symbol)
            shares = request.form.get("shares")
            try:
                int(shares)
            except:
                return apology("Integer!", 400)
            shares = float(shares)

            x = db.execute("SELECT shares FROM main WHERE user=? AND symbol=?", user, symbol)
            for i in range(len(x)):
                availableShares = x[i].get("shares")

            if float(availableShares) < shares:
                return apology("not enough shares to sell")

            # calculate income
            search = lookup(symbol)
            price = float(search["price"])

            income = price*shares

            # update available shares
            availableShares = availableShares - shares

            if availableShares == 0:
                db.execute("DELETE FROM main WHERE user=? and symbol=?", user, symbol)
            else:
                db.execute("UPDATE main SET shares=? WHERE user=? AND symbol=?", availableShares, user, symbol)

            # update users table - cash
            y = db.execute("SELECT cash FROM users WHERE id=?", user)
            for i in range(len(y)):
                cash = y[i].get("cash")

            cash = cash + income
            db.execute("UPDATE users SET cash =? WHERE id=?", cash, user)

            # update history table
            # time code from https://www.programiz.com/python-programming/datetime/current-time
            now = datetime.now()
            transactionTime = now.strftime("%Y-%m-%d %H:%M:%S")
            print(transactionTime)
            db.execute("INSERT INTO history (symbol, shares, price, time, user) VALUES (:symbol, :shares, :price, :time, :user)",
                       symbol=symbol, shares=shares*-1, price=price, time=transactionTime, user=user)
            return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    user = session["user_id"]
    if request.method == "GET":
        return render_template("addcash.html")
    else:

        # update cash
        newcash = float(request.form.get("newcash"))
        if newcash <= 0 or newcash == "":
            return apology("please insert a positive number")

        y = db.execute("SELECT cash FROM users WHERE id=?", user)
        for i in range(len(y)):
            cash = y[i].get("cash")

        cash = cash + newcash
        db.execute("UPDATE users SET cash =? WHERE id=?", cash, user)

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
