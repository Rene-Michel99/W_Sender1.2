import socket
import os

def abre():
    os.system('netsh advfirewall firewall add rule name="PYTINPASS" protocol=TCP dir=in localport=57000 action=allow')

def fecha():
    os.system('netsh advfirewall firewall delete rule name="PYTINPASS" protocol=tcp localport=57000')
def abrew():
    os.system('runas /profile /user:LAPTOP-E3CIF4TI\michelpadilha9745@outlook.com "netsh advfirewall firewall add rule name="PYTINPASS" protocol=TCP dir=in localport=57000 action=allow')

def abrei():
    os.system('AbrirPort2.bat')

name=socket.gethostname()
ip=socket.gethostbyname(name)
print('Sempre.py iniciado')
print('ip: ',ip)
print('status: aguardando conexão...')

port=57000
host=(ip,port)
#abrei()
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

sock.bind((ip,port))

sock.listen(1)

conn ,addr= sock.accept()
print('conectado a ',addr)
sock.close()
conn.close()
#fecha()

