import socket
import os

def azura(cont,dire,tam):
    dire=dire+'/loadSend.txt'
    arq2=open(dire,'w')
    cont=(cont/tam)*100
    print(cont,'%')
    arq2.write(str(cont))
    arq2.close() 

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

cwd=os.path.realpath(__file__)
cwd=cwd[:-9]
cwd=azurawrath(cwd)

arquivo=open(cwd+'/ip.txt','r')
HOST=arquivo.read()
arquivo.close()
PORT = 57000

bonito=cwd+'/path.txt'
print("2",bonito)

arq = open(bonito,'r')
asr=arq.read()
arq.close()

tam=os.path.getsize(asr)
print(tam)

print('Envia.py iniciado')
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
try:
    s.connect((HOST,PORT))
    print('conectando a ',HOST)
    
    arq = open(asr, 'rb')
    cont=0

    for i in arq.readlines():
        s.send(i)
        cont+=len(i)
        azura(cont,cwd,tam)
        
    arq.close()
    s.close()
    print('Arquivo enviado com sucesso!')
    arq=open(cwd+'/loadSend.txt','w')
    arq.write('0')
    arq.close()
except:
    print('não foi possivel efetuar conexão')
    s.close()
