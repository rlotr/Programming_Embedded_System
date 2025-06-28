import socket
import sys

def send_command(ip, port, cmd):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((ip, port))
            print(f"Connected to {ip}:{port}")
            s.sendall((cmd + "\n").encode())
            response = s.recv(1024).decode()
            print(f"Response: {response.strip()}")
    except Exception as e:
        print(f"Error: {e}")

def main():
    if len(sys.argv) != 3:
        print("Usage: python led_tcp_client.py <IP_ADDRESS> <PORT>")
        sys.exit(1)

    ip = sys.argv[1]
    port = int(sys.argv[2])

    print("Available commands:")
    print("LED-ON")
    print("LED-OFF")
    print("STATUS")
    print("Type QUIT to exit.")

    while True:
        cmd = input("Enter command: ").strip()
        cmd = cmd.upper()
        if cmd == "QUIT":
            break
        send_command(ip, port, cmd)

if __name__ == "__main__":
    main()
