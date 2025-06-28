import socket

HOST = '0.0.0.0'
PORT = 8080

def main():
    print(f"TCP Server listening on port {PORT}...")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()

        try:
            while True:
                conn, addr = s.accept()
                with conn:
                    print(f"\nConnection from {addr}")

                    data = conn.recv(1024)
                    if data:
                        print(f"Message received: {data.decode().strip()}")

                        response = "Hello from Python server!\n"
                        conn.sendall(response.encode())
                        print("Response sent. Waiting for next connection...")

        except KeyboardInterrupt:
            print("\nServer stopped by user.")

if __name__ == "__main__":
    main()
