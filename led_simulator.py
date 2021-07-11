from colr import color
from time import sleep
from typing import List, NamedTuple
import socket
import re

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port


class Color(NamedTuple):
    red: int
    green: int
    blue: int


def print_strip(leds: List[Color]):
    strip = "".join(color("  ", back=tuple(x)) for x in leds)
    print(strip, end="\r")



if __name__ == "__main__":
    leds = [Color(0, 0, 0)] * 30

    #for index, item in enumerate(leds):
    #    leds[index] = Color(0, 120, 250)

    #print([str(led) for led in leds])
    


    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        while True:
            conn, addr = s.accept()
            with conn:
                #print('Connected by', addr)
                #while True:
                #while True:
                data = conn.recv(1024)
                #print('Received', repr(data))
                if  data:
                    conn.sendall(b'OK')
                    str_ = data.decode()
                    res = re.match(r'(-?\d+) (\d+) (\d+) (\d+)', str_)
                    if res:
                        index = int(res[1])
                        red = int(res[2])
                        green = int(res[3])
                        blue = int(res[4])
                        if index == -1:
                            # some code to reder strip
                            print_strip(leds)
                        else:
                            leds[index] = Color(red, green, blue)
                    
    print()
