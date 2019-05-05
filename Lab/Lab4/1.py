from flask import Flask
from flask import jsonify
import requests

app = Flask(__name__)

@app.route('/')
def hello():
    result = requests.get('https://thingspeak.com/channels/698947/feeds.json?key=PIGU600LAG50NJ3T&results=10').json()['feeds']
    return jsonify(result)

if __name__ == '__main__':
    app.run()