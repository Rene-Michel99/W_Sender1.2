import socket
import os

host=('192.168.1.4',57000)
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

sock.connect(host)

message='bilada'

sock.send(message)

sock.close()

