from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs

# === server configuration ===
HOST = '0.0.0.0'
PORT = 5000

# === system status ===
led_state = "OFF"
last_timestamp = "-"
last_temp = "-"
last_hum = "-"

# === Alert threshold (in °C) ===
TEMP_THRESHOLD = 30.0

class IoTRequestHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        """Receives data from Arancino via HTTP POST"""
        global last_temp, last_hum, last_timestamp

        length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(length).decode('utf-8')
        data = parse_qs(post_data)

        last_timestamp = data.get('timestamp', [''])[0]
        last_temp = data.get('temp', [''])[0]
        last_hum = data.get('hum', [''])[0]

        print(f"\n Dati ricevuti:")
        print(f"    {last_timestamp} | ️ {last_temp} °C |  {last_hum} %")

        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.end_headers()
        self.wfile.write(b"OK")

    def do_GET(self):
        """Handles GET requests: dashboard, command and toggle"""
        global led_state

        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.end_headers()
            html = self.render_dashboard()
            self.wfile.write(html.encode('utf-8'))

        elif self.path == '/command':
            # Returns the LED state to Arancino
            self.wfile.write(f"LED={led_state}".encode('utf-8'))			
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.send_response(200)			

        elif self.path.startswith('/toggle'):
            # Change LED state and redirect to dashboard
            led_state = "OFF" if led_state == "ON" else "ON"
            print(f"️  Stato LED cambiato: {led_state}")
            self.send_response(303)
            self.send_header('Location', '/')
            self.end_headers()

        else:
            self.send_error(404, "Not Found")

    def render_dashboard(self):
        """Generate the dashboard HTML page"""
        try:
            temp_val = float(last_temp)
        except ValueError:
            temp_val = -999

        is_over = temp_val > TEMP_THRESHOLD
        temp_color = "#d00" if is_over else "#000"

        alert_section = ""
        if is_over:
            alert_section = f"""
            <div style='padding:10px; background:#ffd2d2; border:1px solid red; color:#900; margin:15px 0;'>
                 <b>Warning:</b>Temperature exceeds {TEMP_THRESHOLD} &degC !
            </div>
            """

        return f"""
        <!DOCTYPE html>
        <html>
        <head>
            <title>Smart Dashboard</title>
            <meta http-equiv="refresh" content="10">
            <style>
                body {{
                    font-family: sans-serif; text-align: center; background: #f0f0f0;
                }}
                .card {{
                    background: #fff; display: inline-block; margin-top: 40px;
                    padding: 30px; border-radius: 10px; box-shadow: 0 0 10px #ccc;
                }}
                h1 {{ color: #333; }}
                .value {{ font-size: 1.6em; margin: 12px 0; }}
                .btn {{
                    padding: 12px 24px; background: #007BFF; color: #fff;
                    border: none; border-radius: 5px; font-size: 16px; cursor: pointer;
                }}
            </style>
        </head>
        <body>
            <div class="card">
                <h1>Environmental Dashboard</h1>
                {alert_section}
                <p class="value"><b>{last_timestamp}</b></p>
				<p class="value" style="color:{temp_color}">Temperature: <b>{last_temp} &degC</b></p>
                <p class="value">Humidity: <b>{last_hum} %</b></p>
                <p class="value">LED State: <b>{led_state}</b></p>
                <form action="/toggle" method="get">
                    <button class="btn">Toggle LED</button>
                </form>
            </div>
        </body>
        </html>
        """

    def log_message(self, format, *args):
        """Disable standard HTTP logs"""
        return

def run_server():
    print(f"Server started on http://{HOST}:{PORT}  -  CTRL+C to Stop")
    server = HTTPServer((HOST, PORT), IoTRequestHandler)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nServer stopped manually.")

if __name__ == '__main__':
    run_server()
