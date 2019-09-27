import socket
import os

arq=open('ip.txt','r')
ip=arq.read()
arq.close()

port=57000

os.system("AbreUDP.bat")

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

sock.connect((ip,port))

message='0'
sock.send(message.encode())

os.system("FechaUDP.bat")
