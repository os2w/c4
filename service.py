from flask import (
	Flask, request
)
import subprocess as sp
import os.path

import json

app = Flask(__name__, static_url_path='', static_folder='fe')

@app.route("/")
def root():
	return app.send_static_file("index.html")

@app.post("/solve")
def solve():
	if 'r' not in request.form or \
		'b' not in request.form or \
		'moves' not in request.form:
		return json.dumps({"ok": False, "why": "invalid request"})

	r = request.form['r']
	b = request.form['b']
	moves = request.form['moves']

	res = sp.run(["be/bin/c4", r, b, moves], capture_output=True).stdout.decode("ascii")

	return json.dumps({
		"ok": True,
		"res": res
	})

if __name__ == '__main__':
	if os.path.isfile("be/bin/c4"):
		app.run(host="0.0.0.0", port=4414)
	else:
		print("!!! c4 binary not found in current directory")
