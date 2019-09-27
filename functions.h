#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include<thread>
void invertSlash(std::string &currentFolder){
    for(unsigned int i=0;i<currentFolder.size();i++){
        if(currentFolder[i]=='\\'){
            currentFolder[i] = '/';
        }
    }
}
std::string getCurrentFolder(){
    char currentFolder[100];
    GetCurrentDirectoryA(sizeof(currentFolder), currentFolder);

    for(size_t i=0;i<sizeof(currentFolder)-1;i++){
        if(currentFolder[i]=='\\'){
            currentFolder[i]='/';
        }
    }
    std::stringstream ss;
    ss << currentFolder;
    return ss.str();
}
void MataThreadzumbi(std::string caminho)
{
    std::stringstream s3;
    s3 << "\"" << caminho << "/IntThread.bat" << "\"";
    std::string aux=s3.str();
    system(aux.c_str());
}
void setdefpath(std::string caminho)
{
    std::string path=getCurrentFolder();
    std::stringstream ss;
    ss<< caminho << "/Donwloads";
    std::string aux=ss.str();

    FILE *fp;
    fp=fopen("save.txt","w");
    fprintf(fp,"%s",aux.c_str());
    fclose(fp);
}

void setdefault(std::string caminho)
{
    std::stringstream ss;
    ss<<caminho<<"/notifica.txt";
    std::string aux=ss.str();
    ss.str("");
    ss<<caminho<<"/loadReceive.txt";
    std::string aux2=ss.str();
    ss.str("");
    ss<<caminho<<"/loadSend.txt";
    std::string aux3=ss.str();
    ss.str("");
    ss<<caminho<<"/ip.txt";
    std::string aux4=ss.str();

    FILE *noti;
    noti=fopen(aux.c_str(),"w");
    fprintf(noti,"null\n");
    fclose(noti);

    FILE *ld;
    ld=fopen(aux2.c_str(),"w");
    fprintf(ld,"0");
    fclose(ld);

    FILE *ls;
    ls=fopen(aux3.c_str(),"w");
    fprintf(ls,"0");
    fclose(ls);

    FILE *ip;
    ip=fopen(aux4.c_str(),"w");
    fclose(ip);
}

void recusar(){
    std::cout << "Recusar\n";
    system("Recusar.py");

}

void aceitar(){
    system("Nit.py");
    system("Recb.py");
}



void updateLoading(sf::RectangleShape &load, float percent, char type){
    float width = 0;
    if(type=='s'){
        width = 5.85;
    } else if(type=='r'){
        width = 5.95;
    }

    float newSize = width * percent;
    load.setSize(sf::Vector2f(newSize,load.getSize().y));

}


void saveInfo(std::string userName, std::string ipCrypt, std::string currentFolder){

    std::stringstream ss;
    ss << currentFolder << "/src/user.txt";

    FILE *file = fopen(ss.str().c_str(),"w");
    ss.str("");

    ss << userName << ipCrypt;

    fprintf(file,"%s", ss.str().c_str());
    fclose(file);


}

bool mouseColision(sf::Sprite &sprite, sf::RenderWindow &window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousebounds = window.mapPixelToCoords(mousePos);

    if(sprite.getGlobalBounds().contains(mousebounds)){
        return true;
    }
    return false;
}

bool mouseColision(sf::RectangleShape &sprite, sf::RenderWindow &window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousebounds = window.mapPixelToCoords(mousePos);

    if(sprite.getGlobalBounds().contains(mousebounds)){
        return true;
    }
    return false;
}


std::string abrir(){
    OPENFILENAME ofn;
    OPENFILENAME ofnBKP;

    char fileName[100];
    char fileType[50] = "All Files\0*.*";

    ZeroMemory(&ofn,sizeof(OPENFILENAME));
    ofnBKP = ofn;

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFile = fileType;
    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    std::stringstream ss;
    ss << ofn.lpstrFile;



    /// trocando a barra invertida pela barra comum
    std::string replaces = ss.str();
    for(unsigned int i=0;i<replaces.size();i++){
        if(replaces[i]=='\\'){
            replaces[i]='/';
        }

    }

    ofn = ofnBKP;
    return replaces;
}




std::string getFileNameFromPath(std::string filePath){
    std::stringstream ss;
    const int size = filePath.size();
    char filename[size];
    char filenameAux[size];

    /// Copia do std::string para array de char
    /// o array de char recebe a string invertida
    /// em seguida copiarei a string até o prim. /  e inverterei novamente
    /// restara apenas o nome do arquivo
    for(int i=0;i<size;i++){
        filenameAux[i]=filePath[(size-1)-i];
    }
    filenameAux[size] = '\0';

    /// Pegando array de char ate o /
    /// indexOfEnd vai indicar o indice do /0
    int indexOfEnd=0;
    for(int i=0;i<size;i++){
        if(filenameAux[i] != '/'){
            filename[i]=filenameAux[i];
        } else {
            filename[i]='\0';
            indexOfEnd = i;
            break;
        }
    }

    /// Gravando o streamstream com array de char, invertendo novamente para voltar ao normal
    for(int i=1;i<indexOfEnd+1;i++){
        ss << filename[indexOfEnd-i];
    }

    std::cout << ss.str() << std::endl;
    return ss.str();

}

void removeNameAllFILES(std::string &path){
    for(int i=0;i<10;i++){
        path.pop_back();
    }

}

std::string codificar(std::string ip){
    int bloco[4]={0,0,0,0}, indiceBloco=3, pot=0;

    for(int i=ip.size()-1;i>=0;i--){
        if(ip[i]=='.'){
            indiceBloco--;
            pot=0;
        } else {

            bloco[indiceBloco] = bloco[indiceBloco] + (ip[i]-48) * pow(10,pot);
            pot++;
        }
    }



    std::stringstream ss;
    ss << '_';
    if(bloco[0]==192 && bloco[1]==168){
        ss << 'A';
    } else {
        ss << bloco[0] << "%" << bloco[1];
    }
    ss  << "%" << bloco[2] << "%" << bloco[3];

    return ss.str();
}

std::string decodifica(std::string ip){

    if(ip.size()!=0){

    std::stringstream ss;

    for(int i=ip.size()-1; ip[i]!='_';i--){
        ss << ip[i];
    }

    std::string newIp = ss.str();
    ss.str("");

    if(newIp[newIp.size()-1]=='A'){
        ss << "192.168.";
    }

    short pot = 0;
    int buffer = 0;
    std::vector<int> sequence;
    for(int i=0;i<newIp.size();i++){
        if(newIp[i]!='%'){
            buffer = buffer + (newIp[i] - 48) * pow(10,pot);
            pot++;
        } else {
            sequence.push_back(buffer);
            pot=0;
            buffer=0;
        }
    }

    if(newIp[newIp.size()-1]=='A'){
        ss << sequence[1] << "." << sequence[0];
    } else {
        sequence.push_back(buffer);
        ss << sequence[3] << "." << sequence[2] << "." << sequence[1] << "." << sequence[0];
    }

    return ss.str();
    }
}


#endif // FUNCTIONS_H_INCLUDED
