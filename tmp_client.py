# Echo client program
import socket

HOST = '127.0.0.7'    # The remote host
PORT = 50007              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'0 0 250 0')
    data = s.recv(1024)
    s.sendall(b'1 250 0 0')
    data = s.recv(1024)
    s.sendall(b'3 0 0 250')
    data = s.recv(1024)
    s.sendall(b'-1 0 0 0')
    data = s.recv(1024)
print('Received', repr(data))
