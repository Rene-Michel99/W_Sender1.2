#ifndef CONNECT_C_H_INCLUDED
#define CONNECT_C_H_INCLUDED
#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
#include <windows.h>

void enviarTCP(std::string ip, int port, std::string path);
void receberTCP(int port, std::string pathSaida);
int getFileSize(std::string path);



void enviarTCP(std::string ipServer, int port,std::string path){
    sf::TcpSocket socket;
    sf::Packet packet;
    bool endOfFile=false;


    if(socket.connect(ipServer,port)==sf::Socket::Done){
        std::cout << "Conectado!\n";

        int timerSeg        = 0;
        int sizeFileByte    = 0;
        int contBytesSended = 0;
        int kbps            = 0;
        float percent       = 0;
        sf::Clock clock;

        sizeFileByte = getFileSize(path);

        FILE *file = fopen(path.c_str(),"rb");

        int c;
        while((c=fgetc(file))!=EOF){
            packet << endOfFile << c << percent;
            socket.send(packet);
            packet.clear();
            contBytesSended++;
            percent = (100/(float)sizeFileByte) * (float)contBytesSended;
/*
            if(clock.getElapsedTime().asSeconds()>1){

                timerSeg++;
                system("cls");
                printf("Enviando...\n");
                printf("  %d seg >> Tamanho: %d bytes   Enviado: %d bytes   %.2f%%  ", timerSeg, sizeFileByte, contBytesSended, percent);
                printf(":: %.2f kbps", ((float)(contBytesSended - kbps))/100);
                clock.restart();
                kbps = contBytesSended;
            }
*/
        }
        endOfFile = true;
        packet << endOfFile << c;
        socket.send(packet);
        packet.clear();
        fclose(file);
    } else {
        std::cout << "--- ERRO ---\n";
    }


}

void receberTCP(int port, std::string pathSaida){
    std::cout << "Escutando..\n";
    sf::TcpSocket socket;
    sf::Packet packet;
    sf::TcpListener listener;

    listener.listen(port);
    listener.accept(socket);

    int c;
    bool endOfFile=false;
    float percent;
    sf::Clock clock;

    FILE *file = fopen(pathSaida.c_str(), "wb");
    while(!endOfFile){
        socket.receive(packet);
        packet >> endOfFile >> c >> percent;
        fputc(c,file);
        packet.clear();
        /*
        if(clock.getElapsedTime().asSeconds()>1){
            system("cls");
            printf("Recebendo: %.2f%%", percent);
        }
        */
    }
    fclose(file);
}

int getFileSize(std::string path){
        /// Ver tamanho do arquivo em bytes:
        int sizeFileByte=0;
        FILE *file = fopen(path.c_str(),"rb");
        while(fgetc(file)!=EOF){
            sizeFileByte++;
        }
        fclose(file);
        //printf("Tam>> %d bytes\n",sizeFileByte);
        return sizeFileByte;
}


#endif // CONNECT_C_H_INCLUDED
