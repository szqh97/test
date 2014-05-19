#!/usr/bin/env python
# Redirect function is used to forward user to full url if he came
# from shortened
# Request is used to encapsulate HTTP request. It will contain request
# method, request arguments and other related information
from flask import redirect, render_template, request, Flask 
from werkzeug.exceptions import BadRequest, NotFound

import models

# Initialize Flask application
app = Flask(__name__, template_folder='views')

@app.route("/")
def index():
    """Renders main page."""
    return render_template("main_page.html")

@app.route("/shorten/")
def shorten():
    """Returns short_url of requested full_url."""
    #Validate user input
    full_url = request.args.get("url")
    if not full_url:
        raise BadRequest()
    
    # Model returns object with short_url property
    url_model = models.Url.shorten(full_url)

    # Pass data to view and call its render method
    short_url = request.host + '/' + url_model.short_url
    return render_template("success.html", short_url = short_url)
@app.route('/<path:path>')
def redirect_to_full(path=''):
    """Gets short url and redirects user to corresponding full url if found . """
    #Model returns object width full_url property
    url_model = models.Url.get_by_short_url(path)

    # validate model return 
    if not url_model:
        raise NotFound()
    return rediret(url_model.full_url)

if __name__ == "__main__":
    app.run(debug=True)
