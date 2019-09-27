
import socket
import os
from tkinter import *

def tela():
    root=Tk()
    root.geometry("250x100")
    root.title("MESSAGE BOX")
    root.iconbitmap('favicon.ico')
    
    label=Label(root,text="Arquivo baixado com sucesso!",font=("brandish","10","bold"))
    label.pack()

    button=Button(root,text="OK",command=root.destroy)
    button.pack()
    root.mainloop()

def azurawrath(path):
    for i in range(2,len(path)):
        if path[i]=='\\':
            path=list(path)
            path[i]='/'
    path[0]='c'
    path=''.join(path)
    hed=''.join(path)
    j=0
    hed=path[2:len(path)]
    return hed

def getam(origem):
    arq=open(origem+'/notifica.txt','r')
    tam=arq.readlines()
    arq.close()
    return tam[2]

def azura(cont,origem,tam):
    arq=open(origem+'/loadReceive.txt','w')
    cont=(cont/tam)*100
    print(cont,'%')
    arq.write(str(cont))
    arq.close()

def abre():
    os.system('netsh advfirewall firewall add rule name="PYTINPASS" protocol=TCP dir=in localport=57000 action=allow')

def fecha():
    os.system('netsh advfirewall firewall delete rule name="PYTINPASS" protocol=tcp localport=57000')

    
HOST=socket.gethostname()
HOST=socket.gethostbyname(HOST)
PORT=57000

cwd=os.path.realpath(__file__)
cwd=cwd[:-8]
cwd=azurawrath(cwd)
print(cwd)

arq = open(cwd+'/save.txt','r')
path=arq.read()
arq.close()
path=azurawrath(path)

arq=open(cwd+'/notifica.txt','r')
name=arq.readline()
arq.close()

name=name[:-1]
print(path)
print(name)
tam=getam(cwd)
tam=int(tam)
print(tam,'B')

print('Recb.py iniciado')

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#abre()
s.bind((HOST, PORT))
s.listen(1)

conn, addr=s.accept()

print('conectado a',addr)
arq = open(path+'/'+name, 'wb')
cont=0
while 1:
    dados=conn.recv(1024)
    cont+=len(dados)
    if not dados:
        break
    arq.write(dados)
    azura(cont,cwd,tam)

arq.close()
conn.close()
print('arquivo recebido!')
#fecha()

tela()

arq=open('notifica.txt','w')
arq.write('null\n')
arq.close()

