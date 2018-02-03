from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # TODO
    
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    pos_count = 0
    neg_count = 0
    neut_count = 0
    for i in range(len(tweets)):
        score = analyzer.analyze(tweets[i])
        if score > 0.0:
            pos_count += 1
        elif score < 0.0:
            neg_count += 1
        else:
           neut_count += 1

    
    total_count = pos_count + neg_count + neut_count
    positive = (pos_count/total_count)*100
    negative = (neg_count/total_count)*100
    neutral = (neut_count/total_count)*100

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
