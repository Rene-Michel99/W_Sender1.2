import socket
import os

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

def azuraacha(carga):
    for i in range(0,len(carga)):
        if carga[i]=='/':
            carga=carga[:i:]
            break
    return carga

def getam(origem):
    arq=open(origem+'\path.txt','r')
    path=arq.read()
    arq.close()
    return os.path.getsize(path)

def checaerro(origem):
    arq=open(origem+'\ip.txt','r')
    info=arq.read()
    arq.close()

    if not info:
        print('(ip não informado)')
    elif len(info)<len('192.168.0.1'):
        print('(ip informado está fora do padrão/tamanho mínimo do ip',len('192.168.0.1'),')')
    else:
        print('(ip informado recusou a conexão ou não está disponível)')
    

origem=os.path.realpath(__file__)

origem=origem[:-11]
origem=azurawrath(origem)

arquivo=open(origem+'\ip.txt','r')
host=arquivo.read()
arquivo.close()

port=57000
print('Notifica.py iniciado')

print(origem)
tam=getam(origem)
print('tamanho: ',tam,'Bytes')

arq=open(origem+'path.txt','r')
carga=arq.read()
arq.close()

carga=azuraacha(carga[::-1])
carga=carga[::-1]
print('nome: ',carga)

arq=open(origem+'notifica.txt','w')
arq.write(carga+'\n'+'Azura'+'\n'+str(tam))
arq.close()
print('notifica.txt atualizado')
print('conectando...')

sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
try:
    sock.connect((host,port))

    print('CONECTADO!')

    arq=open(origem+'notifica.txt','rb')

    for i in arq.readlines():
        sock.send(i)
        print(len(i))
        
    arq.close()
    sock.close()
    print('Notifica.txt enviado!')
except:
    print('Não foi possivel efetuar conexão')
    checaerro(origem)
    sock.close()

