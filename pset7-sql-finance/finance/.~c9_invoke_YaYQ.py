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

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
###############START: EXTRA IMPLEMENTATION TO BUY AND SELL################
    if request.method == "POST":
        #GET USER STOCK DATA
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
            #TODO: WILL NEED TO EITHER ADD MISSING VARIABLES FROM OTHER LOOP HERE OR DO SOMETHING LATER FOR HTML TO LOAD PROPERLY
        total_money = usd(total_stocks+user_cash)

        #DO USER BUYING
        req_quant_list = []
        temp_dict = {}
        total_cost = 0
        #CREATE DICTIONARY OF REQUESTED QUANTIIES FOR BUY
        for i in range(len(stocks)):
            #ENSURES STRINGS ARE ZERO INSTEAD OF EMPTY
            if len(request.form.get("buy_share_quant_" + str(stocks[i]['symbol']))) == 0:
                temp_dict = {'symbol' : str(stocks[i]['symbol'])}
                req_quant_list.insert(i, temp_dict.copy())
                req_quant_list[i]['req_quant'] = 0
                req_quant_list[i]['price'] = stocks[i]['price']
                req_quant_list[i]['total_stock_cost'] = float(req_quant_list[i]['price'] * req_quant_list[i]['req_quant'])
                
            else:
                temp_dict = {'symbol' : str(stocks[i]['symbol'])}
                req_quant_list.insert(i, temp_dict.copy())
                req_quant_list[i]['req_quant'] = int(request.form.get("buy_share_quant_" + str(stocks[i]['symbol'])))
                req_quant_list[i]['price'] = stocks[i]['price']
                req_quant_list[i]['total_stock_cost'] = float(req_quant_list[i]['price'] * req_quant_list[i]['req_quant'])
                total_cost += float(stocks[i]['price']) * float(request.form.get("buy_share_quant_" + str(stocks[i]['symbol'])))
        
        #PERFORM THE BUY
        if float(user_cash) >= float(total_cost):
            for i in range(len(req_quant_list)):
                db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id", total_cost=req_quant_list[i]['total_stock_cost'], user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=req_quant_list[i]['symbol'], shares=req_quant_list[i]['req_quant'], price=req_quant_list[i]['total_stock_cost'], datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
            
        #SELL OPERATIONS
        req_quant_list_sell = []
        temp_dict = {}
        total_cost = 0
        #CREATE DICTIONARY OF REQUESTED QUANTIIES FOR SELL
        for i in range(len(stocks)):
            #ENSURES STRINGS ARE ZERO INSTEAD OF EMPTY
            if len(request.form.get("sell_share_quant_" + str(stocks[i]['symbol']))) == 0:
                temp_dict = {'symbol' : str(stocks[i]['symbol'])}
                req_quant_list_sell.insert(i, temp_dict.copy())
                req_quant_list_sell[i]['req_quant'] = 0
                req_quant_list_sell[i]['price'] = stocks[i]['price']
                req_quant_list_sell[i]['total_stock_cost'] = float(req_quant_list_sell[i]['price'] * req_quant_list_sell[i]['req_quant'])
                
            else:
                temp_dict = {'symbol' : str(stocks[i]['symbol'])}
                req_quant_list_sell.insert(i, temp_dict.copy())
                req_quant_list_sell[i]['req_quant'] = int(request.form.get("sell_share_quant_" + str(stocks[i]['symbol'])))
                req_quant_list_sell[i]['price'] = stocks[i]['price']
                req_quant_list_sell[i]['total_stock_cost'] = float(req_quant_list_sell[i]['price'] * req_quant_list_sell[i]['req_quant'])
                total_cost += float(stocks[i]['price']) * float(request.form.get("sell_share_quant_" + str(stocks[i]['symbol'])))
        
        #PERFORM THE SELL
        if float(user_cash) >= float(total_cost):
            for i in range(len(req_quant_list_sell)):
                db.execute("UPDATE users SET cash = cash + :total_cost WHERE id = :user_id", total_cost=req_quant_list_sell[i]['total_stock_cost'], user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=req_quant_list_sell[i]['symbol'], shares=-int(req_quant_list_sell[i]['req_quant']), price=-float(req_quant_list_sell[i]['total_stock_cost']), datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
            
        #RELOAD PAGE
      
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
  ###############END: EXTRA IMPLEMENTATION TO BUY AND SELL################          
    else:
        try:
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
            if len(stocks)>0:
                return render_template("index.html", stocks=stocks, total_stocks=total_stocks, user_cash=user_cash_formatted, total_money=total_money)
            else:
                return render_template("index_nobuysell.html", stocks=stocks, total_stocks=total_stocks, user_cash=user_cash_formatted, total_money=total_money)
        except:
            return render_template("index_nobuysell.html", user_cash=usd(10000),total_money=usd(10000))
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
            if float(user_cash[0]['cash']) >= float(total_cost):
                db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id", total_cost=total_cost, user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=symbol, shares=req_quant, price=total_cost, datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
                #RELOAD DATA
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
                    #TODO: WILL NEED TO EITHER ADD MISSING VARIABLES FROM OTHER LOOP HERE OR DO SOMETHING LATER FOR HTML TO LOAD PROPERLY
                total_money = usd(total_stocks+user_cash)
                return render_template("buy.html")
            else:
                return apology("Insufficient cash")
            
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    try:
        stocks = db.execute("SELECT symbol, shares, time FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
        for i in range(len(stocks)):
            data = lookup(stocks[i]['symbol'])
            stocks[i]['price'] = data['price']
            stocks[i]['name'] = data['name']
            stocks[i]['price'] = usd(stocks[i]['price'])
        return render_template("history.html", stocks=stocks)
    except:
        return apology("No transaction history, buy some stocks!")



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
    
        # insert username into database
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))
        
        # remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        #session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username", username=request.form.get("username"))
        #session["user_id"] = rows[0]["id"]
        # redirect user to home page
        return redirect(url_for("index"))
        #return render_template("login.html")
        #return render_template("index_nobuysell.html", user_cash=usd(10000),total_money=usd(10000))
    
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
            user_shares_total = 0
            print("test3 above")
            for i in range(len(user_shares)):
                user_shares_total += user_shares[i]['shares']
            if int(req_quant) <= user_shares_total:
                db.execute("UPDATE users SET cash = cash + :total_cost WHERE id = :user_id", total_cost=total_cost, user_id=session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :datetime)", user_id=session["user_id"], symbol=symbol, shares=-int(req_quant), price=-total_cost, datetime = time.strftime('%Y-%m-%d %H:%M:%S'))
                #RELOAD DATA
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
                total_money = usd(total_stocks+user_cash)
                return render_template("sell.html")
            else:
                return apology("Insufficient shares")
            
    else:
        return render_template("sell.html")





