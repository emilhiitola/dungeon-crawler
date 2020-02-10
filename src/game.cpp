#include "game.hpp"
        
void Game::Render(sf::RenderWindow& window, Player& P, std::shared_ptr<Room> R, Renderer& ren, bool changedroom) {
    switch(CurrentState) {
        case Play:
            window.clear();
            if (changedroom) {
                ren.RenderRoom(R,true);}
            else {
                ren.RenderRoom(R,false);}
            ren.RenderPlayer(P);
            ren.RenderAttributes(P);
            ren.RenderException(ex);
            window.display();
            break;
        case Paused:
            window.clear(sf::Color::Black);
            ren.RenderPaused();
            window.display();
            break;
        case Info:
            window.clear(sf::Color::White);
            ren.RenderInstructions();
            window.display();
            break;
        case Inventory:
            window.clear(sf::Color::Black);
            ren.RenderInventory(P);
            window.display();
            break;
        case Dead:
            window.clear(sf::Color::Black);
            ren.RenderDead(P);
            window.display();
            break;
        case Win:
            window.clear(sf::Color::Black);
            ren.RenderWin(P);
            window.display();
            break;
        default:
            window.clear();
    }
}
void Game::MonsterTurn(std::shared_ptr<Room> R) {
    for (auto m : R->getMonsters()){
        m->turn();
    }
}

void Game::Update(Player& P) {
    if (P.getHP() <= 0) {
        CurrentState = Dead;
    }
    else if (P.getScore() >= WinScore) {
        CurrentState = Win;
    }
}
std::shared_ptr<Room> Game::processEvent(sf::Event& event, Player& P, std::shared_ptr<Room> R) {
    if (event.type == sf::Event::Closed) {
        running = false;

    }
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (CurrentState == Play) {
            try{
                if (event.key.code == sf::Keyboard::P){
                    CurrentState = Paused;
                    return R;
                }
                if(event.key.code==sf::Keyboard::F){
                    CurrentState=Inventory;
                    return R;
                }
                if (event.key.code == sf::Keyboard::W) {
                    if(P.MoveR(NORTH)){
                        R=P.getRoom();
                    }
                }
                if (event.key.code == sf::Keyboard::A) {
                    if(P.MoveR(WEST)){
                        R=P.getRoom();
                    }
                }
                if (event.key.code == sf::Keyboard::S) {
                    if(P.MoveR(SOUTH)){
                        R=P.getRoom();
                    }               
                }
                if (event.key.code == sf::Keyboard::D) {
                    if(P.MoveR(EAST)){
                        R=P.getRoom();
                    }
                }
                if (event.key.code == sf::Keyboard::Space) {
                    P.hit();
                }
                if (event.key.code == sf::Keyboard::LShift) {
                    P.usePotion();
                    return R;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    P.changeWeapon();
                    return R;
                }
                if (event.key.code == sf::Keyboard::E) {
                    P.changePotion();
                    return R;
                }
                if(event.key.code==sf::Keyboard::Z){
                    P.upgradeWeapon(0);
                }
                if(event.key.code==sf::Keyboard::X){
                    P.upgradeWeapon(1);
                }
                if(event.key.code==sf::Keyboard::C){
                    P.upgradePotion();
                }
                if (event.key.code == sf::Keyboard::V) {
                    P.deleteItem(Wep);    
                }
                if (event.key.code == sf::Keyboard::B) {
                    std::shared_ptr<Potion> pt = P.getPotion();  
                    P.deleteItem(Pot);
                }
            }
            catch(InventoryException &e){
                ex=e.GetError();
            }
            try{
                if (!P.turn()) {
                    MonsterTurn(R);
                }
            }
            catch(...){ }
                
            }
        if (CurrentState == Paused) {
            if (event.key.code == sf::Keyboard::P) {
                CurrentState = Play;
            }
            if (event.key.code == sf::Keyboard::Q) {
                running = false;
            }
            if (event.key.code == sf::Keyboard::I) {
                CurrentState = Info;
            }
        }
        if (CurrentState == Info) {
            if (event.key.code == sf::Keyboard::Escape ) {
                CurrentState = Paused;
            }
        }
        if (CurrentState==Inventory){
            if (event.key.code==sf::Keyboard::F || event.key.code == sf::Keyboard::Escape){
                CurrentState=Play;
            }
        }
        if (CurrentState == Dead) {
            if (event.key.code== sf::Keyboard::Q) {
                running = false;
            }
        }
        if (CurrentState == Win) {
            if (event.key.code == sf::Keyboard::Q) {
                running = false;
            }
            if (event.key.code == sf::Keyboard::C) {
                CurrentState = Play;
                WinScore = 1000000;
            }
        }
    }
    return R;
}

void Game::InitandRun() {
    running = true;
    CurrentState = Paused; 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler");
    
    Renderer ren = Renderer(window);
    ren.FetchResources();
    Map map = Map::createMap(20,20);
    std::shared_ptr<Room> R =   map.getRooms()[0];
    ren.MakeDrawables(R);
    
    Player P = Player(300,10,std::make_pair(5,6),R);
    P.getInventory().addItem(std::make_shared<Weapon>(Weapon(Bow,40)));
    P.changeWeapon();
    R->AddMonster(3,3,P);
    R->setPlayerLocation(P.Getlocation());
    while (running){
        Update(P);
        sf::Event event;
        
        while (window.pollEvent(event)){

            std::shared_ptr<Room> R1 = processEvent(event, P, R);
            if (R1 == R) {
                Render(window,P,R1,ren);
            }
            else {
                Render(window,P,R1,ren,true);
            }
            R = R1;
        }
        
    }
}