import socket
import os

name=socket.gethostname()
ip=socket.gethostbyname(name)
port=57000

print('seu ip: ',ip)

os.system("AbreUDP.bat")

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

sock.bind((ip,port))

message=sock.recvfrom(1024)

print('message: ',message[0].decode())
print('ip :',message[1])

arq=open("confirma.txt","w")
arq.write(message[0].decode())
arq.close()

os.system("FechaUDP.bat")
