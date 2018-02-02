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
