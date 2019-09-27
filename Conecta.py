
import socket
import os

def azurawrath():
    path=os.path.realpath(__file__)
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

def abre():
    os.system('netsh advfirewall firewall add rule name="PYTINPASS" protocol=TCP dir=in localport=57000 action=allow')

def fecha():
    os.system('netsh advfirewall firewall delete rule name="PYTINPASS" protocol=tcp localport=57000')

cwd=azurawrath()
cwd=cwd[:-10]
print(cwd)

arquivo=open(cwd+'/ip.txt','r')
ip=arquivo.read()
arquivo.close()

port=57000

#abre()

print('Conecta.py iniciado\nconectando a',ip)
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.connect((ip,port))
    print('conectado!')

    messsage='envia'
    s.send(message)
    s.close()
    #fecha()
except:
    print('Não foi possivel efetuar conexão')
    #fecha()
    s.close()
