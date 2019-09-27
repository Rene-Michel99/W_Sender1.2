import socket
import os

def abre():
    os.system('netsh advfirewall firewall add rule name="PYTINPASS" protocol=TCP dir=in localport=57000 action=allow')

def fecha():
    os.system('netsh advfirewall firewall delete rule name="PYTINPASS" protocol=tcp localport=57000')

def abrei():
    os.system('AbrirPort2.bat')

def escreve(conn):
    arq=open("notifica.txt",'wb')
    while True:
        dados=conn.recv(1024)
        if not dados:
            break
        arq.write(dados)
    arq.close()

def testa(conn):
    message=conn.recv(1024)
    print(message.decode())


name=socket.gethostname()
ip=socket.gethostbyname(name)
port=57000

print('Nit.py iniciado\nAguardando conexão...')
#abrei()
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

try:
    sock.bind((ip,port))
    sock.listen(1)
    conn,addr=sock.accept()

    arq=open("notifica.txt",'wb')
    while True:
        dados=conn.recv(1024)
        if not dados:
            break
        arq.write(dados)
    arq.close()
    
    sock.close()

    print('Notifica.txt recebido com sucesso!')
except:
    sock.close()
print('Nit.py encerrado')
#fecha()
