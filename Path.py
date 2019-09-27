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

cwd=os.path.realpath(__file__)
cwd=cwd[:-7]

cwd=azurawrath(cwd)
cwd='C:'+cwd

arq=open('caminho.txt','w')
arq.write(cwd)
arq.close()
