import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get all relevant information from the DB for the portfolio
    shares = db.execute("SELECT u.username, u.cash, t.symbol, SUM(t.shares) as shares FROM users u INNER JOIN transactions t ON u.id = t.user_id WHERE u.id = ? GROUP BY t.symbol", session["user_id"])
    # Get the user's current cash amount
    user = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    if not shares:
            return render_template("index.html",cash=usd(user[0]["cash"]), final_total=usd(user[0]["cash"]))
    # Dictionary to save all current data of each stock that the user owns
    portfolio = []
    cash = shares[0]["cash"]
    # Final total is the the worth of the whole portfolio
    final_total = cash
    for row in shares:
        if row["shares"] != 0:
            # Make a dictionary to save data of each stock separatly
            dict_row = {'symbol': None, 'shares': None, 'price': None, 'total': None, 'final_total': None}
            dict_row["symbol"] = row["symbol"]
            dict_row["shares"] = row["shares"]
            # Check the current price of the shares
            dict_row["price"] = usd(float((lookup(row["symbol"]))["price"]))
            total = float((lookup(row["symbol"]))["price"] * float(dict_row["shares"]))
            dict_row["total"] = usd(float((lookup(row["symbol"]))["price"] * float(dict_row["shares"])))
            final_total += total
            # Finally append the data into the portfolio list
            portfolio.append(dict_row)
        else:
            final_total = cash
    return render_template("index.html" , portfolio=portfolio, cash=usd(cash), final_total=usd(final_total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Check wrether the user gave a valid amount
        try:
            shares = int(shares)
        except ValueError:
            return apology("Invalid number of shares.")
        # Check for invalid symbol, empty input, shares lower than 1
        if not symbol or (lookup(symbol) is None) or shares < 1:
            return apology("Could not buy.")

        stock = lookup(symbol)
        price = stock["price"] * shares

        # Get user data from db
        currentUser = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        user_cash = currentUser[0]["cash"]
        # Check if user can afford the stocks in request
        if user_cash < price:
            return apology("Not enough money.")
        # Execute the transaction
        db.execute("INSERT INTO transactions(user_id, symbol, shares, price, total, transacted, stat) VALUES(?, ?, ?, ?, ?, ?, ?);", session["user_id"], symbol, shares, stock["price"], price, datetime.now(), "buy") # From the datetime library
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", (user_cash - price), session["user_id"])

        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


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
    if request.method == "POST":
        symbolInput = request.form.get("symbol")
        # Check if input is not empty or invalid
        quote = lookup(symbolInput)
        if not symbolInput or quote == None:
            return apology("Input invalid.")
        return render_template("quoted.html", stock=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        data = db.execute("SELECT username FROM users")
        users = [user["username"] for user in data]
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Check for all types of wrong inputs
        if not username or not password or not confirmation or (password != confirmation) or (username in users):
            if not username:
                return apology("Please choose a username.")
            elif username in users:
                return apology("Username already exists. Please choose a different one.")
            elif not password:
                return apology("Please enter a password.")
            elif password != confirmation:
                return apology("Passwords do not match.")
            else:
                return apology("Error.")
        # Hash the password
        pwHash = generate_password_hash(password)
        # Insert into the db
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, pwHash)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        symbols = db.execute("SELECT symbol, shares FROM transactions where user_id = ? and stat = 'buy'", session["user_id"])

        # Check for valid amount of shares: not less than 1 and not more than the user has in his portfolio
        bought_shares = db.execute("SELECT sum(shares) AS sum FROM TRANSACTIONS WHERE SYMBOL=? AND STAT='buy' AND USER_ID = ?", symbol, session["user_id"])
        if shares < 1 or shares > int(bought_shares[0]["sum"]):
            return apology("Invalid amount of shares selected.")
        # Check wrether the user has this stock
        if symbol not in [symb["symbol"] for symb in symbols]:
            return apology("Stock selected is not found in your account.")

        # Lookup latest updates
        stock_data = lookup(symbol)
        # The amount the user will get once sold
        sell_total = stock_data["price"] * shares
        # Get all data from user from DB
        user_data = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
        # Get current cash of the user
        user_cash = user_data[0]["cash"]

        # Update user's cash amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", (user_cash + sell_total), session["user_id"])

        # Insert a new transaction in the DB
        db.execute("INSERT INTO transactions(user_id, symbol, shares, price, total, transacted, stat) VALUES(?, ?, ?, ?, ?, ?, ?);", session["user_id"], symbol, -shares, stock_data["price"], sell_total, datetime.now(), "sell") # From the datetime library
        return redirect("/")
    else:
        # Get all the stock symbols you have
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions where user_id = ? and stat = 'buy'", session["user_id"])
        if not symbols:
            return apology("Nothing to sell.")
        return render_template("sell.html", symbols=symbols)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Get stock quote."""
    if request.method == "POST":
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")
        # Get the current password for comparison
        current_password = db.execute("SELECT hash FROM USERS WHERE id=?", session["user_id"])
        # Check if the input is not empty & the old_password is correct
        if not old_password or not check_password_hash(current_password[0]["hash"], old_password):
            return apology("Old password is incorrect.")
        # Check if the inputs for the new passwords match
        if not new_password or not confirmation:
            return apology("Make sure to fill in both inputs.")
        # Check if the new password and the confirmation match
        if new_password != confirmation:
            return apology("The passwords do not match.")
        # Hash the new password
        hashed_password = generate_password_hash(new_password)
        # Update the DB
        db.execute("UPDATE users SET hash=? WHERE id=?", hashed_password, session["user_id"])
        flash("Password successfully changed!")
        return redirect("/")
    return render_template("change_password.html")
