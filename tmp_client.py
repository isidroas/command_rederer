# Echo client program
import socket

HOST = '127.0.0.7'    # The remote host
PORT = 50007              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    
    s.sendto(b'0 0 250 0', (HOST, PORT))
    s.sendto(b'1 250 0 0', (HOST, PORT))
    s.sendto(b'3 0 0 250', (HOST, PORT))
    s.sendto(b'-1 0 0 0', (HOST, PORT))
