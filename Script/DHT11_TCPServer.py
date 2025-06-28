import socket

HOST = '0.0.0.0'
PORT = 8080

def main():
    print(f"TCP Server listening on port {PORT}...\n")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()

        try:
            while True:
                conn, addr = s.accept()
                with conn:
                    print(f"Connection from {addr}")
                    data = conn.recv(1024)
                    if data:
                        print("Received:", data.decode().strip())
						
        except KeyboardInterrupt:
            print("\nServer manually stopped.")

if __name__ == "__main__":
    main()
