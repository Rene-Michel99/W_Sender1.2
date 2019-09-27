#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void initText(sf::Text *text, sf::Font &font){
    text[0].setString("");
    text[1].setString("");
    text[2].setString("arquivo.rar");
    text[3].setString("Warton_2a3d5wf");
    text[4].setString("C:/");
    text[5].setString("Usuário");

    char aux[100];
    FILE *file = fopen("src/user.txt", "r");

    std::stringstream ss;
    fscanf(file,"%s",aux);
    ss << aux;
    text[5].setString(ss.str());
    fclose(file);

    ss.str("");
    file = fopen("src/folder.txt", "r");
    fscanf(file,"%s",aux);
    ss << aux;
    text[4].setString(ss.str());
    fclose(file);

    text[0].setFillColor(sf::Color(0,0,0,255));
    text[0].setFont(font);
    text[0].setCharacterSize(20);
    text[0].setPosition(80,125);

    text[1].setFillColor(sf::Color(0,0,0,255));
    text[1].setFont(font);
    text[1].setCharacterSize(20);
    text[1].setPosition(80,216);

    text[2].setFillColor(sf::Color(255,255,255));
    text[2].setFont(font);
    text[2].setCharacterSize(20);
    text[2].setPosition(147,352);

    text[3].setFillColor(sf::Color(255,255,255));
    text[3].setFont(font);
    text[3].setCharacterSize(20);
    text[3].setPosition(147,386);

    text[4].setFillColor(sf::Color(255,255,255));
    text[4].setFont(font);
    text[4].setCharacterSize(15);
    text[4].setPosition(147,452);

    text[5].setFillColor(sf::Color(255,204,0));
    text[5].setFont(font);
    text[5].setCharacterSize(16);
    text[5].setPosition(404,47);

}

void initSpritesBT(sf::Texture *texture, sf::Sprite *sprite){
    texture[0].loadFromFile("src/bt_open.png");
    texture[1].loadFromFile("src/bt_send.png");
    texture[2].loadFromFile("src/bt_acept.png");
    texture[3].loadFromFile("src/icon_1.png");
    texture[4].loadFromFile("src/icon_2.png");
    texture[5].loadFromFile("src/icon_3.png");
    texture[6].loadFromFile("src/bt_refuse.png");

    for(int i=0;i<7;i++){
        sprite[i].setTexture(texture[i]);
    }
    sprite[0].setPosition(540,126);
    sprite[1].setPosition(540,217);
    sprite[2].setPosition(486,381);
    sprite[3].setPosition(88,352);
    sprite[4].setPosition(92,392);
    sprite[5].setPosition(88,453);
    sprite[6].setPosition(630,381);
}


#endif // INIT_H_INCLUDED
