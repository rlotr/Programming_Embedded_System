import socket

HOST = '192.168.1.22'  	# Server IP address
PORT = 8090        		# Socket port number

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'Hello, Server!')
    data = s.recv(1024)

print(f"Server response: {data.decode()}")