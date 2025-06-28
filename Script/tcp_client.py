import socket
import time
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python tcp_client.py <SERVER_IP> <PORT>")
        sys.exit(1)

    esp_ip = sys.argv[1]
    esp_port = int(sys.argv[2])

    for i in range(10):
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((esp_ip, esp_port))
                message = f"HELLO {i+1}\n"
                s.sendall(message.encode())
                data = s.recv(1024)
                print(f"[{i+1}/10] Received: {data.decode().strip()}")
        except Exception as e:
            print(f"[{i+1}/10] Error: {e}")

        time.sleep(6)  # wait for 6 secs

if __name__ == "__main__":
    main()
