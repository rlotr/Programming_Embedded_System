from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs

HOST = '0.0.0.0'
PORT = 5000

# Global variables to store the last reading
last_timestamp = "-"
last_temp = "-"
last_hum = "-"

class SensorWebHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        global last_timestamp, last_temp, last_hum

        content_length = int(self.headers.get('Content-Length', 0))
        post_body = self.rfile.read(content_length).decode('utf-8')
        data = parse_qs(post_body)

        last_timestamp = data.get('timestamp', [''])[0]
        last_temp = data.get('temp', [''])[0]
        last_hum = data.get('hum', [''])[0]

        print(f"\nNew data:")
        print(f"{last_timestamp} | {last_temp} °C | {last_hum} %")

        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.end_headers()
        self.wfile.write(b"OK")

    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.end_headers()
            html = f"""
            <!DOCTYPE html>
            <html>
            <head>
                <title>Arancino DHT11 Dashboard</title>
                <meta http-equiv="refresh" content="5">
                <style>
                    body {{ font-family: sans-serif; text-align: center; background: #f4f4f4; }}
                    .card {{ background: #fff; display: inline-block; margin-top: 50px;
                             padding: 20px; border-radius: 8px; box-shadow: 0 0 10px #ccc; }}
                    h1 {{ color: #333; }}
                    .value {{ font-size: 2em; margin: 10px 0; }}
                </style>
            </head>
            <body>
                <div class="card">
                    <h1>Sensor Dashboard</h1>
                    <p class="value"><b>{last_timestamp}</b></p>
                    <p class="value">Temperature: <b>{last_temp} &degC</b></p>
                    <p class="value">Humidity: <b>{last_hum} %</b></p>
                    <p style="color:gray;">(Auto-refresh every 5s)</p>
                </div>
            </body>
            </html>
            """
            self.wfile.write(html.encode('utf-8'))
        else:
            self.send_error(404, "Not Found")

    def log_message(self, format, *args):
        return  # Disable standard HTTP logging

def run_server():
    print(f"HTTP Server with Dashboard on http://{HOST}:{PORT}")
    print("Send POST to /, open browser to /, CTRL+C to Stop")
    server = HTTPServer((HOST, PORT), SensorWebHandler)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nServer stopped.")

if __name__ == '__main__':
    run_server()
