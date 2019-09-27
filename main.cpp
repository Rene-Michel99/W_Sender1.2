#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include "init.h"
#include "functions.h"
#include<stdlib.h>
#include<thread>
#include"connect_C.h"

class GLOBALTHREAD
{
public:

    GLOBALTHREAD()
    : th1(&GLOBALTHREAD::f, this),th2(&GLOBALTHREAD::f2,this),th3(&GLOBALTHREAD::f3,this)
    {
    }

public:

    void f()
    {
        printf("Thread 1 iniciada\n");
        if(cont)
        {
            std::stringstream s2;
            s2<< "\"" <<path<<"Sempre.py"<< "\"" ;
            printf("ok");
            system(s2.str().c_str());
        }
        else
            system("Sempre.py");
        printf("Thread 1 encerrada\n");
    }
    void f2()
    {
        /*std::stringstream s2;
        s2<<path<<"Recusar.py";
        system(s2.str().c_str());*/
        system("Recusar.py");
    }
    void f3()
    {
        /*std::stringstream s2,s3;
        s2<<path<<"Nit.py";
        s3<<path<<"Recb.py";
        //system("Confirma.py")
        system(s2.str().c_str());
        system(s3.str().c_str());*/
        system("Nit.py");
        system("Recb.py");
    }

    sf::Thread th1;
    sf::Thread th2;
    sf::Thread th3;
    std::string path;
    bool cont=false;
};
bool is_th1=true,is_th2=false,is_th3=false,is_send=false;
void f0(std::string path)
{
    //system("netsh advfirewall firewall add rule name=""PYTINPASS"" protocol=TCP dir=in localport=57000 action=allow");
    //system("runas /profile /user:LAPTOP-E3CIF4TI\michelpadilha9745@outlook.com ""netsh advfirewall firewall add rule name=""PYTINPASS"" protocol=TCP dir=in localport=57000 action=allow");
    printf("Thread 1 iniciada\n");
    std::stringstream s2;
    s2<< "\"" <<path<<"/Sempre.py"<< "\"" ;
    std::string aux=s2.str();
    s2.str("");

    s2<< "\""<<path<<"/Nit.py"<< "\"";
    std::string aux2=s2.str();

    system(aux.c_str());
    Sleep(250);
    system(aux2.c_str());
    is_th1=false;
}

void f1(std::string path)
{
    is_th2=true;
    std::stringstream s2;
    s2<< "\""<<path<<"/Recusar.py"<< "\"";
    std::string aux=s2.str();
    system(aux.c_str());
    is_th2=false;
}
void f2(std::string path)
{
    is_th3=true;
    printf("Thread 2 iniciada\n");

    std::stringstream s2;
    s2<< "\""<<path<<"/Recb.py"<< "\"";
    std::string aux=s2.str();
    //system("Confirma.py")
    system(aux.c_str());
    is_th3=false;
}
void enviar(std::string currentFolder){
    is_send=true;
    std::stringstream ss;
    ss << "\"" << currentFolder << "/Envia.py" << "\"" ;
    std::string aux = ss.str();
    printf("%s",aux.c_str());
    ss.str("");

    ss << "\"" << currentFolder << "/Notifica.py" << "\"";
    std::string aux2=ss.str();
    ss.str("");

    ss << "\"" << currentFolder << "/Conecta.py" << "\"";
    std::string aux3=ss.str();
    invertSlash(aux3);
    invertSlash(aux2);
    invertSlash(aux);

    //system("\Users\Marco Aurelio\Documents\Projects\Projeto_Processo\Conecta.py")
    system(aux3.c_str());
    Sleep(300);
    system(aux2.c_str());
    Sleep(500);
	system(aux.c_str());
    is_send=false;
}

WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,LPSTR l, int i){
//int main(){
    sf::RenderWindow window(sf::VideoMode(700,500), "");
    window.setFramerateLimit(40);

    sf::Texture textureBG;
    textureBG.loadFromFile("src/bg.png");
    sf::Sprite spriteBG;
    spriteBG.setTexture(textureBG);

    sf::Texture textureBG_Error;
    textureBG_Error.loadFromFile("src/bg_error.png");
    sf::Sprite spriteBG_Error;
    spriteBG_Error.setTexture(textureBG_Error);


    sf::Texture textureBT[7];
    sf::Sprite spriteBT[7];
    initSpritesBT(textureBT,spriteBT);


    sf::Font font;
    font.loadFromFile("src/Courier.otf");
    sf::Text text[6];
    initText(text, font);

    sf::Color colorGreen      = sf::Color::Green;
    sf::Color colorLightGreen = sf::Color(0,255,0,80);
    sf::RectangleShape rectUserTosend;
    rectUserTosend.setSize(sf::Vector2f(431,30));
    rectUserTosend.setFillColor(sf::Color(0,0,0,0));
    rectUserTosend.setOutlineColor(sf::Color(0,0,0,0));
    rectUserTosend.setOutlineThickness(2);
    rectUserTosend.setPosition(68,217);

    sf::RectangleShape rectUserName;
    rectUserName.setSize(sf::Vector2f(140,24));
    rectUserName.setFillColor(sf::Color(0,0,0,0));
    rectUserName.setOutlineColor(sf::Color(0,0,0,0));
    rectUserName.setOutlineThickness(2);
    rectUserName.setPosition(399,47);

    sf::RectangleShape loadingSend;
    loadingSend.setSize(sf::Vector2f(565,3));
    loadingSend.setFillColor(sf::Color(0,255,0));
    loadingSend.setPosition(57,269);

    sf::RectangleShape loadingReceive;
    loadingReceive.setSize(sf::Vector2f(565,3));
    loadingReceive.setFillColor(sf::Color(255,102,0));
    loadingReceive.setPosition(53,432);

    std::string filePath;             /// Caminho onde o arquivo que será enviado está
    std::string fileName;             /// Nome do arquivo que será enviado
    std::string folderToReceiver;     /// Pasta que receberá o arquivo baixado
    std::string userName = "user";    /// Nome de usuário
    std::string ipCrypt  = sf::IpAddress::getLocalAddress().toString(); /// Código do IP criptografado
    //std::string ipCrypt  = codificar(sf::IpAddress::getLocalAddress().toString());
    std::string userToSend;
    std::string currentFolder;
    bool checar=false;

    std::stringstream ss;
    char currentFolderExe[100];
    GetCurrentDirectory(100,currentFolderExe);
    ss << currentFolderExe;
    currentFolder = ss.str();
    ss.str("");

    GLOBALTHREAD central;
    std::string caminho=getCurrentFolder();
    sf::Thread th1(&f0,caminho);
    sf::Thread th2(&f1,caminho);
    sf::Thread th3(&f2,caminho);
    th1.launch();
    setdefpath(caminho);

    float ld1=0;
    float ld2=0;
    FILE *file = fopen("load.txt","r");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                fclose(file);
                setdefault(caminho);
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                std::stringstream ss;
                ss << currentFolder << "/acept_refuse.txt";
                FILE *file = fopen(ss.str().c_str(),"w");
                fprintf(file,"%d",0);
                fclose(file);

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
                saveInfo(userName,ipCrypt,currentFolder);

            }

            if(event.type == sf::Event::TextEntered && rectUserTosend.getFillColor().a > 0 ){

                char c = static_cast<char>(event.text.unicode);
                static std::stringstream ss;
                std::string textEntered = ss.str();

                if(c != 0x08){
                    ss << c;
                } else if(c == 0x08 && textEntered.size()!=0){
                    textEntered.pop_back();
                    ss.str("");
                    ss << textEntered;
                }
                textEntered = ss.str();
                text[1].setString(textEntered);

                std::stringstream ss2;
                ss2 << currentFolder << "/ip.txt";
                FILE *file = fopen(ss2.str().c_str() , "w");

                fprintf(file,"%s", textEntered.c_str());
                fclose(file);

            }
            if(event.type == sf::Event::TextEntered && rectUserName.getFillColor().a > 0 ){

                char c = static_cast<char>(event.text.unicode);
                static std::stringstream ss;
                std::string textEntered = ss.str();

                if(c != 0x08){
                    ss << c;
                } else if(c == 0x08 && textEntered.size()!=0){
                    textEntered.pop_back();
                    ss.str("");
                    ss << textEntered;
                }
                textEntered = ss.str();
                userName    = textEntered;

                std::stringstream ss2;
                ss2 << userName << ipCrypt;
                text[5].setString(ss2.str());
                userToSend  = ss2.str();
                /// Atualizar o tamanho do quadrado da ediçaodo username:
                rectUserName.setSize(sf::Vector2f(text[5].getGlobalBounds().width + 12 , rectUserName.getSize().y));

            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                rectUserTosend.setFillColor(sf::Color(0,0,0,0));
                rectUserTosend.setOutlineColor(sf::Color(0,0,0,0));
                rectUserName.setFillColor(sf::Color(0,0,0,0));
                rectUserName.setOutlineColor(sf::Color(0,0,0,0));

                if(mouseColision(spriteBT[0], window)){
                    std::cout << "Abrir\n";


                    ss << currentFolder << "/path.txt";
                    std::string folder = ss.str();
                    ss.str("");
                    invertSlash(folder);


                    filePath = abrir();
                    fileName = getFileNameFromPath(filePath);
                    text[0].setString(fileName);

                    FILE *file = fopen(folder.c_str(),"w");
                    fprintf(file,"%s",filePath.c_str());
                    fclose(file);

                    checar=true;

                } else if(mouseColision(spriteBT[1], window) && checar){
                    printf("enviar");

                    th1.terminate();
                    is_th1=false;
                    static sf::Thread ted(&enviar,currentFolder);
                    ted.launch();
                    MataThreadzumbi(caminho);

                    //th1.launch();


                } else if(mouseColision(spriteBT[2], window)){
                    //aceitar();
                    th1.terminate();
                    is_th1=false;
                    th3.launch();
                    MataThreadzumbi(caminho);

                    //th1.launch();
                } else if(mouseColision(spriteBT[5], window)){
                    std::cout << "Pasta destino\n";
                    folderToReceiver = abrir();
                    removeNameAllFILES(folderToReceiver);
                    text[4].setString(folderToReceiver);

                    ss << currentFolder << "/save.txt";
                    std::string folder2 = ss.str();
                    ss.str("");
                    invertSlash(folder2);


                    printf(">> %s", folderToReceiver.c_str());

                    FILE *file = fopen(folder2.c_str(),"w");
                    fprintf(file,"%s",folderToReceiver.c_str());
                    fclose(file);

                }
                if(mouseColision(rectUserTosend,window)){
                    if(rectUserTosend.getFillColor() == sf::Color(0,0,0,0)){
                        rectUserTosend.setFillColor(colorLightGreen);
                        rectUserTosend.setOutlineColor(colorGreen);
                    } else {
                        rectUserTosend.setFillColor(sf::Color(0,0,0,0));
                        rectUserTosend.setOutlineColor(sf::Color(0,0,0,0));
                    }
                }
                if(mouseColision(rectUserName,window)){
                    if(rectUserName.getFillColor() == sf::Color(0,0,0,0)){
                        rectUserName.setFillColor(colorLightGreen);
                        rectUserName.setOutlineColor(colorGreen);
                    } else {
                        rectUserName.setFillColor(sf::Color(0,0,0,0));
                        rectUserName.setOutlineColor(sf::Color(0,0,0,0));
                    }
                } else if(mouseColision(spriteBT[6], window)){
                    recusar();
                }
            }
        }

        if(mouseColision(spriteBT[0],window)){
            short r = spriteBT[0].getColor().r;
            short g = spriteBT[0].getColor().g;
            short b = spriteBT[0].getColor().b;
            short a = 120;
            spriteBT[0].setColor(sf::Color(r,g,b,a));
        } else {
            spriteBT[0].setColor(sf::Color(255,255,255,255));
        }

        if(mouseColision(spriteBT[1],window)){
            short r = spriteBT[1].getColor().r;
            short g = spriteBT[1].getColor().g;
            short b = spriteBT[1].getColor().b;
            short a = 120;
            spriteBT[1].setColor(sf::Color(r,g,b,a));
        } else {
            spriteBT[1].setColor(sf::Color(255,255,255,255));
        }

        if(mouseColision(spriteBT[2],window)){
            short r = spriteBT[2].getColor().r;
            short g = spriteBT[2].getColor().g;
            short b = spriteBT[2].getColor().b;
            short a = 120;
            spriteBT[2].setColor(sf::Color(r,g,b,a));
        } else {
            spriteBT[2].setColor(sf::Color(255,255,255,255));
        }

        if(mouseColision(spriteBT[5],window)){
            short r = spriteBT[5].getColor().r;
            short g = spriteBT[5].getColor().g;
            short b = spriteBT[5].getColor().b;
            short a = 120;
            spriteBT[5].setColor(sf::Color(r,g,b,a));
        } else {
            spriteBT[5].setColor(sf::Color(255,255,255,255));
        }

        if(mouseColision(spriteBT[6],window)){
            short r = spriteBT[6].getColor().r;
            short g = spriteBT[6].getColor().g;
            short b = spriteBT[6].getColor().b;
            short a = 120;
            spriteBT[6].setColor(sf::Color(r,g,b,a));
        } else {
            spriteBT[6].setColor(sf::Color(255,255,255,255));
        }

        window.clear(sf::Color::White);
        window.draw(spriteBG);

        for(int i=0;i<6;i++){
            window.draw(text[i]);
        }
        for(int i=0;i<7;i++){
            window.draw(spriteBT[i]);
        }

        std::stringstream ss2;
        ss2  << currentFolder << "/loadSend.txt"  ;

        FILE *FLS;
        FLS = fopen(ss2.str().c_str(),"r");
        fscanf(FLS,"%f",&ld1);
        updateLoading(loadingSend,ld1,'s');
        fclose(FLS);
        ss2.str("");

        ss2  << currentFolder << "/loadReceive.txt"  ;

        FILE *FLR;
        FLR=fopen(ss2.str().c_str(),"r");
        fscanf(FLR,"%f",&ld2);
        updateLoading(loadingReceive,ld2,'r');
        fclose(FLR);
        ss2.str("");

        ss2  << currentFolder << "/notifica.txt"  ;

        std::stringstream info;
        file = fopen(ss2.str().c_str(),"r");
        char c;
        while((c=fgetc(file))!='\n'){
            info << c;
        }
        if(strcmp(info.str().c_str(),"null")){
            text[2].setString(info.str());
            spriteBT[2].setPosition(486,381);
            spriteBT[6].setPosition(630,381);
        } else {
            text[2].setString("");
            spriteBT[2].setPosition(1000,0);
            spriteBT[6].setPosition(1000,0);
        }
        info.str("");

        while((c=fgetc(file))!=EOF){
            info << c;
        }
        text[3].setString(info.str());
        fclose(file);

        ss2.str("");

        window.draw(rectUserTosend);
        window.draw(rectUserName);
        window.draw(loadingSend);
        window.draw(loadingReceive);

        std::stringstream ss3;
        ss3 << currentFolder << "/acept_refuse.txt";
        file = fopen(ss3.str().c_str(),"r");
        int cod;
        fscanf(file,"%d",&cod);
        if(cod!=0){
            spriteBG_Error.setColor(sf::Color(255,255,255,255));
        } else {
            spriteBG_Error.setColor(sf::Color(0,0,0,0));
        }
        fclose(file);

        window.draw(spriteBG_Error);
        window.display();
        int check=is_send+is_th1+is_th2+is_th3;
        if(check==0)
        {
            is_th1=true;
            //setdefault(caminho);
            th1.launch();
        }
    }
    th1.terminate();
    MataThreadzumbi(caminho);
    return 0;
}
