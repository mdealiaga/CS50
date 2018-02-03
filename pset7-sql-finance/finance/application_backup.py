from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
import time

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    #let's get one share to show first
    stocks = db.execute("SELECT symbol, sum(shares) AS shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING sum(shares) > 0", user_id=session["user_id"])
    extra_data = []
    total_stocks = 0
    user_cash_dict = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    user_cash = user_cash_dict[0]['cash']
    user_cash_formatted = usd(user_cash)
    for i in range(len(stocks)):
        data = lookup(stocks[i]['symbol'])
        stocks[i]['price'] = data['price']
        stocks[i]['name'] = data['name']
        stocks[i]['total'] = (data['price'] * stocks[i]['shares'])
        total_stocks += stocks[i]['total']
        stocks[i]['price'] = usd(stocks[i]['price'])
        stocks[i]['total'] = usd(stocks[i]['total'])
    total_money = usd(total_stocks+user_cash)
    return render_template("index.html", stocks=stocks, total_stocks=total_stocks, user_cash=user_cash_formatted, total_money=total_money)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Stock does not exist")
        else:
            share_price = quote['price']
            name = quote['name']
            symbol = quote['symbol']
            req_quant = request.form.get("share_quant")
            total_cost = float(req_quant) * share_price
            user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
            print(type(user_cash))
            print(user_cash)
            print(user_cash[0]['cash'])
            if float(user_cash[0]['cash']) >= float(total_cost):
                db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id", total_cost=total_cost, user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=symbol, shares=req_quant, price=total_cost, datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
                return render_template("index.html")
            else:
                return apology("Insufficient cash")
            
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    stocks = db.execute("SELECT symbol, shares, time FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    for i in range(len(stocks)):
        data = lookup(stocks[i]['symbol'])
        stocks[i]['price'] = data['price']
        stocks[i]['name'] = data['name']
        stocks[i]['price'] = usd(stocks[i]['price'])
    return render_template("history.html", stocks=stocks)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Stock does not exist")
        else:
            price = usd(quote['price'])
            name = quote['name']
            symbol = quote['symbol']
            return render_template("quote_display.html", price=price, name=name, symbol=symbol)
            #name=name, price=price, symbol=symbol
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
    
        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
            
        elif request.form.get("password") != request.form.get("password_confirmation"):
            return apology("passwords must match")
    
        # query database for username
        rows = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))
    
        # remember which user has logged in
        session["user_id"] = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
    
        # redirect user to home page
        return redirect(url_for("index"))
    
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Stock does not exist")
        else:
            share_price = quote['price']
            name = quote['name']
            symbol = quote['symbol']
            req_quant = request.form.get("share_quant")
            total_cost = float(req_quant) * share_price
            user_shares = db.execute("SELECT sum(shares) AS shares FROM transactions GROUP BY shares HAVING user_id = :user_id AND symbol = :symbol" , user_id=session["user_id"], symbol=symbol)
            print(user_shares)
            print("test above")
            print(user_shares[0]['shares'])
            print("test2 above")
            user_shares_total = 0
            print("test3 above")
            for i in range(len(user_shares)):
                user_shares_total += user_shares[i]['shares']
            print("test4 above")
            print(user_shares_total)
            if int(req_quant) <= user_shares_total:
                db.execute("UPDATE users SET cash = cash + :total_cost WHERE id = :user_id", total_cost=total_cost, user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=symbol, shares=-int(req_quant), price=-total_cost, datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
                return render_template("index.html")
            else:
                return apology("Insufficient shares")
            
    else:
        return render_template("sell.html")





