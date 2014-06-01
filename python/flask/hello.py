#!/usr/bin/evn python
from flask import Flask, render_template, request, session, escape
app = Flask(__name__)

@app.route('/')
def index():
    if 'username' in session:
        return 'Logged in as %s' % escape(session['username'])
    return 'You are not logged in'

@app.route('/login', methods = ['GET', 'POST'])
def login():
    if request.method  == 'POST':
        print request.form
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return '''
    <form action = "" method = "post">
        <p> <input type=text username=username>
        <p> <input type=submit value=login>
    </form>
    '''

@app.route('/logout')
def logout():
    # remove the username from the session if it's there
    session.pop('username', None)
    return redirect(url_for('index'))

app.sercret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
@app.route('/hello/')
@app.route('/hello/<uname>')
def hello(name = None):
    return render_template('hello.html', name = name)

@app.route('/user/<username>')
def show_user_profile(username):
    return 'User %s' % username

@app.route('/post/<int:post_id>')
def show_post(post_id):
    return "post %d" % post_id

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0')
