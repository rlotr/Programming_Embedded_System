import socket

ESP_IP = "192.168.1.36"
ESP_PORT = 8080

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((ESP_IP, ESP_PORT))
        s.sendall(b"HELLO SERVER")
        data = s.recv(1024)
        print("Received from ESP:", data.decode().strip())

if __name__ == "__main__":
    main()
