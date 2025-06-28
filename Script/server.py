import socket
import threading


class TCPServer:
    def __init__(self, ip='192.168.1.78', port=9999):
        self.ip = ip
        self.port = port
        self.server = None
        self.run()

    def run(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.ip, self.port))
        self.server.listen()
        print(f'[*] Listening on {self.ip}:{self.port}')

        while True:
            client, address = self.server.accept()
            print(f'[*] Accepted connection from {address[0]}:{address[1]}')
            client_handler = threading.Thread(target=self.handle_client, args=(client,))
            client_handler.start()

    @staticmethod
    def handle_client(client_socket):
        with client_socket as sock:
            request = sock.recv(1024)
            print(f'[*] Received: {request.decode("utf-8")}')
            sock.send(b'ACK')

def main():
    tcp_server = TCPServer()


if __name__ == '__main__':
    main()
