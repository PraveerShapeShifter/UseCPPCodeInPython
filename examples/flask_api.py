"""Example of how the Flask backend consumes the shapeshifter modules.

Run from the project root (after building the extensions in place):

    python examples/flask_api.py

For production on Windows Server, serve with waitress behind IIS instead of
the Flask dev server:

    waitress-serve --listen=127.0.0.1:8080 examples.flask_api:app
"""

import faulthandler

from flask import Flask, jsonify

from shapeshifter import fabric, maths

# If a native module crashes the process (access violation), print the Python
# stack that was executing instead of dying silently.
faulthandler.enable()

app = Flask(__name__)


@app.get("/api/fabric")
def get_fabric():
    return jsonify(fabric.getFabricDetails().to_dict())


@app.get("/api/project-name")
def get_project_name():
    return jsonify({"name": fabric.getMyName()})


@app.get("/api/add/<int:a>/<int:b>")
def add(a, b):
    return jsonify({"result": maths.add_Numbers(a, b)})


if __name__ == "__main__":
    app.run(port=5000, debug=True)
