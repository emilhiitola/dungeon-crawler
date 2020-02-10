#include "renderer.hpp"
void Renderer::FetchResources() {
    if(!font.loadFromFile("../resources/Arial.ttf")){
        std::cout << "Could not load font" << std::endl;
    }
    if (!WallTexture.loadFromFile("../resources/BrickWall.png")) {
        std::cout << "Could not load wall texture" << std::endl;
    }
    if (!FloorTexture.loadFromFile("../resources/Floor.png")) {
        std::cout << "Could not load floor texture" << std::endl;
    }
    if (!DoorTexture.loadFromFile("../resources/Door.png")) {
        std::cout << "Could not load door texture" << std::endl;
    }
    if (!ItemTexture.loadFromFile("../resources/item.png")) {
        std::cout << "Could not load item texture" << std::endl;
    }
}

const std::string readInstr(){
    std::ifstream is("../resources/inst.txt");
    std::string str;
    std::string line;
    
    if(!is.is_open()){
        return "failed";
    }

    while(is){
        getline(is,line);
        str+="\n"+line;
        
    }
    return str;
}
void Renderer::MakeDrawables(std::shared_ptr<Room> room) {
    int width_ = room->getWidth();
    int height_ = room->getHeight();

    sf::RectangleShape backgroundW(sf::Vector2f((4+width_)*columnSize,(4+height_)*columnSize));
    backgroundW.setPosition(dungeonScreenOffsetX, dungeonScreenOffset);
    backgroundW.setTexture(&WallTexture);
         
    sf::RectangleShape background(sf::Vector2f(width_*columnSize,height_*columnSize));
    background.setPosition(sf::Vector2f(dungeonScreenOffsetX+2*columnSize, dungeonScreenOffset+2*columnSize));
    background.setTexture(&FloorTexture);

    sf::RectangleShape door(sf::Vector2f((float) columnSize, (float) columnSize));
    door.setTexture(&DoorTexture);

    sf::RectangleShape item(sf::Vector2f(15, 15));
    item.setTexture(&ItemTexture);

    sf::RectangleShape enemyRect(sf::Vector2f((float) columnSize, (float) columnSize));
    enemyRect.setFillColor(sf::Color(255,0,0));

    sf::RectangleShape playerrect(sf::Vector2f((float) columnSize, (float) columnSize));
    playerrect.setFillColor(sf::Color(0,0,255));

    sf::RectangleShape exceptionbox(sf::Vector2f(250.f, 55.f));
    exceptionbox.setFillColor(sf::Color(25,25,25));
    exceptionbox.setPosition(520,520);

    sf::RectangleShape healthbargreen(sf::Vector2f((float) 1 , (float) 10));
    healthbargreen.setPosition(20,20);
    healthbargreen.setFillColor(sf::Color::Green);

    sf::RectangleShape healthbarred(sf::Vector2f((float) 1, (float) 10));
    healthbarred.setFillColor(sf::Color::Red);

    sf::RectangleShape xpBar(sf::Vector2f(1, (float) 10));
    xpBar.setPosition(80,20);
    xpBar.setFillColor(sf::Color::White);

    sf::RectangleShape outerXP(sf::Vector2f(50.0,10.0));
    outerXP.setPosition(80,20);
    outerXP.setOutlineThickness(1.f);
    outerXP.setFillColor(sf::Color::Black);
    outerXP.setOutlineColor(sf::Color::White);

    //All drawed when PLAY
    Drawables.push_back(backgroundW);
    Drawables.push_back(background);
    Drawables.push_back(door);
    Drawables.push_back(item);
    Drawables.push_back(enemyRect);
    Drawables.push_back(playerrect);
    Drawables.push_back(exceptionbox);
    Drawables.push_back(healthbargreen);
    Drawables.push_back(healthbarred);
    Drawables.push_back(xpBar);
    Drawables.push_back(outerXP);
    for (unsigned int i = 0; i<(room->getHeight()+4); i++) {
        for (unsigned int j = 0; j<(room->getWidth()+4); j++) {
            if (room->GetTiles()[i][j].GetType() == Door) {
                Drawables[2].setPosition(dungeonScreenOffsetX+j*columnSize,dungeonScreenOffset+i*columnSize);
                Doors.push_back(Drawables[2]);
            }
        }
    }



    
    sf::Text monsterlevel;
    monsterlevel.setFont(font);
    monsterlevel.setCharacterSize(15);
    monsterlevel.setFillColor(sf::Color::Black);

    sf::Text monsterHP;
    monsterHP.setFont(font);
    monsterHP.setCharacterSize(13);
    monsterHP.setFillColor(sf::Color::Red);
    monsterHP.setStyle(sf::Text::Bold);

    sf::Text inventoryheader;
    inventoryheader.setFont(font);
    inventoryheader.setFillColor(sf::Color::White);
    inventoryheader.setString("Inventory");
    inventoryheader.setCharacterSize(25);
    inventoryheader.setPosition(20,20);


    sf::Text weapons;
    weapons.setFont(font);
    weapons.setFillColor(sf::Color::White);
    weapons.setCharacterSize(14);
    weapons.setStyle(sf::Text::Regular);
    weapons.setPosition(20,100);
   
    sf::Text potions;
    potions.setFont(font);
    potions.setFillColor(sf::Color::White);
    potions.setCharacterSize(14);
    potions.setStyle(sf::Text::Regular);
    potions.setPosition(140,100);
    
    sf::Text craftables;
    craftables.setFont(font);
    craftables.setFillColor(sf::Color::White);
    craftables.setCharacterSize(14);
    craftables.setStyle(sf::Text::Regular);
    craftables.setPosition(260,100);



    sf::Text lvl;
    lvl.setFont(font);
    lvl.setCharacterSize(15);
    lvl.setFillColor(sf::Color::White);
    lvl.setStyle(sf::Text::Bold);
    lvl.setPosition(140,15);
    
    sf::Text weapon;
    weapon.setFont(font);
    weapon.setCharacterSize(14);
    weapon.setFillColor(sf::Color::White);
    weapon.setPosition(20,520);
    
    sf::Text potion;
    potion.setFont(font);
    potion.setCharacterSize(14);
    potion.setFillColor(sf::Color::White);
    potion.setPosition(140,520);
    
    sf::Text activepotion;
    activepotion.setFont(font);
    activepotion.setCharacterSize(14);
    activepotion.setFillColor(sf::Color::White);
    activepotion.setPosition(280,520);
   
    sf::Text craftablesPLAY;
    craftablesPLAY.setFont(font);
    craftablesPLAY.setCharacterSize(14);
    craftablesPLAY.setFillColor(sf::Color::White);
    craftablesPLAY.setPosition(20,200);

    sf::Text pausedheader;
    pausedheader.setFont(font);
    pausedheader.setFillColor(sf::Color::White);
    pausedheader.setString("Welcome to Dungeon Crawler!");
    pausedheader.setCharacterSize(30);
    pausedheader.setPosition(50,20);

    sf::Text pausedtext;
    pausedtext.setFont(font);
    pausedtext.setString("Press <P> to play\nPress <Q> to quit\nPress <I> for instructions");
    pausedtext.setCharacterSize(20);
    pausedtext.setFillColor(sf::Color::White);
    pausedtext.setPosition(100,100);
    
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::White);
    score.setPosition(300,10);
    
    sf::Text exception;
    exception.setFont(font);
    exception.setCharacterSize(14);
    exception.setFillColor(sf::Color::White);
    exception.setPosition(522,522);

    sf::Text instructionsheader;
    instructionsheader.setFont(font);
    instructionsheader.setFillColor(sf::Color::Black);
    instructionsheader.setString("Instructions:");
    instructionsheader.setCharacterSize(25);
    instructionsheader.setPosition(20,20);

    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString(readInstr());
    instructions.setFillColor(sf::Color::Black);
    instructions.setCharacterSize(14);
    instructions.setStyle(sf::Text::Regular);
    instructions.setPosition(20,100);

    sf::Text deadtext;
    deadtext.setFont(font);
    deadtext.setFillColor(sf::Color::White);
    deadtext.setCharacterSize(30);
    deadtext.setPosition(20,20);

    sf::Text playerlevel;
    playerlevel.setFont(font);
    playerlevel.setFillColor(sf::Color::White);
    playerlevel.setCharacterSize(20);
    playerlevel.setPosition(200,10);

    sf::Text wintext;
    wintext.setFont(font);
    wintext.setFillColor(sf::Color::White);
    wintext.setCharacterSize(30);
    wintext.setPosition(20,20);
    //drawed when WIN (Texts[0])
    Texts.push_back(wintext);
    //drawed when DEAD (Texts[1])
    Texts.push_back(deadtext);
    //drawed when INFO (Texts[2:3])
    Texts.push_back(instructionsheader);
    Texts.push_back(instructions);
    //drawed when PAUSED (Texts[4:5])
    Texts.push_back(pausedheader);
    Texts.push_back(pausedtext);
    //drawed when INVENTORY (Texts[6:9])
    Texts.push_back(inventoryheader);
    Texts.push_back(weapons);
    Texts.push_back(potions);
    Texts.push_back(craftables);
    //drawed when PLAY(Texts[10:end])
    Texts.push_back(monsterlevel);
    Texts.push_back(score);
    Texts.push_back(weapon);
    Texts.push_back(potion);
    Texts.push_back(activepotion);
    Texts.push_back(craftablesPLAY);
    Texts.push_back(playerlevel);
    Texts.push_back(exception);
    Texts.push_back(monsterHP);//18
}
void Renderer::RenderRoom(std::shared_ptr<Room> room, bool changedroom){
    
    if (changedroom) {
        Drawables[0].setSize(sf::Vector2f( (float)(4+room->getWidth())*columnSize,(float)(4+room->getHeight())*columnSize));
        Drawables[1].setSize(sf::Vector2f((float) room->getWidth()*columnSize,(float) room->getHeight()*columnSize));
        Doors.clear();
    }
    window_.draw(Drawables[0]);
    window_.draw(Drawables[1]);

    
    for (unsigned int i = 0; i<(room->getHeight()+4); i++) {
        for (unsigned int j = 0; j<(room->getWidth()+4); j++) {
            if (changedroom) {
                if (room->GetTiles()[i][j].GetType() == Door) {
                    Drawables[2].setPosition(dungeonScreenOffsetX+j*columnSize,dungeonScreenOffset+i*columnSize);
                    Doors.push_back(Drawables[2]);
                }
            }
            if (room->GetTiles()[i][j].getInventory().getSize() != 0) {
                Drawables[3].setPosition(dungeonScreenOffsetX+j*columnSize,dungeonScreenOffset+i*columnSize);
                window_.draw(Drawables[3]);
            }
        }
    }
    for (auto it : room->getMonsters()) {
        Drawables[4].setPosition(dungeonScreenOffsetX+it->Getlocation().second*columnSize, dungeonScreenOffset+it->Getlocation().first*columnSize);
        Texts[10].setPosition(dungeonScreenOffsetX+(it->Getlocation().second+0.25)*columnSize, dungeonScreenOffset+(it->Getlocation().first)*columnSize);
        Texts[10].setString( std::to_string( it->getLevel() ));
        Texts[18].setPosition(dungeonScreenOffsetX+(it->Getlocation().second)*columnSize, dungeonScreenOffset+(it->Getlocation().first-0.9)*columnSize);
        Texts[18].setString(std::to_string(it->getHP()));
        window_.draw(Drawables[4]);
        window_.draw(Texts[10]);
        window_.draw(Texts[18]);
    } 
    
    for (int i = 0; i < Doors.size(); i++) {
        window_.draw(Doors[i]);
    }
}

void Renderer::RenderPlayer(Player& p){
    std::pair<int, int> playerlocation = p.Getlocation();
    Drawables[5].setPosition(dungeonScreenOffsetX+playerlocation.second*columnSize, dungeonScreenOffset+playerlocation.first*columnSize);
    window_.draw(Drawables[5]);

}
void Renderer::RenderAttributes(Player& P) {

    Drawables[7].setSize(sf::Vector2f((float) 50*(((float) P.getHP())/((float) P.getMaxHP())), (float) 10));
    Drawables[8].setSize(sf::Vector2f((float) 50*(1.0-(((float) P.getHP())/((float)(P.getMaxHP())))), (float) 10));
    Drawables[8].setPosition(20+50*(((float)P.getHP())/((float)P.getMaxHP())),20);
    window_.draw(Drawables[7]);
    window_.draw(Drawables[8]);


    Drawables[9].setSize(sf::Vector2f((float) 50*(((float) P.getXP())/((float) P.getLvlXP())), (float) 10));
    Drawables[10].setSize(sf::Vector2f(50.0,10.0));

    window_.draw(Drawables[10]);
    window_.draw(Drawables[9]);

    Texts[11].setString("Score: " + std::to_string(P.getScore()));
    Texts[12].setString(P.printWeapon());
    Texts[13].setString(P.printPotion());
    Texts[14].setString(P.printAPotion());
    Texts[15].setString(P.getInventory().printCraftables());
    Texts[16].setString("Level: " + std::to_string(P.getLevel()));
    for (int i = 11; i < 17; i++) {
        window_.draw(Texts[i]);
    }
}
void Renderer::RenderException(const std::string& str){
    
    Texts[17].setString(str);
    window_.draw(Drawables[6]);
    window_.draw(Texts[17]);
}
void Renderer::RenderPaused() {
    window_.draw(Texts[4]);
    window_.draw(Texts[5]);
}

//renders help instructions i.e. simple textbox 
void Renderer::RenderInstructions() {
    window_.draw(Texts[2]);
    window_.draw(Texts[3]);
}


void Renderer::RenderInventory(Player& P){
    Texts[7].setString(P.getInventory().printWeapons());
    Texts[8].setString(P.getInventory().printPotions());
    Texts[9].setString(P.getInventory().printCraftables());
    window_.draw(Texts[6]);
    window_.draw(Texts[7]);
    window_.draw(Texts[8]);
    window_.draw(Texts[9]);
}
void Renderer::RenderDead(Player& P) {
    std::stringstream ss;
    ss << "You are Dead\nScore: " << P.getScore() << "\nPress Q to quit";
    std::string string = ss.str();
    Texts[1].setString(string);
    window_.draw(Texts[1]);
}
void Renderer::RenderWin(Player& P) {
    std::stringstream ss;
    ss << "You Win\nScore: " << P.getScore() << "\nPress C to continue\nPress Q to quit";
    std::string string = ss.str();
    sf::Text text;
    Texts[0].setString(string);
    window_.draw(Texts[0]);
}