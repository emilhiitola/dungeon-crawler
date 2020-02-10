#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "room.hpp"
#include "player.hpp"
#include "monster.hpp"

/*
all grafical drawings are made in this class 
game class is always calling a method of this class 
*/
class Renderer {
public:

//constructor making the render window 

    Renderer(sf::RenderWindow& window) : window_(window){
    }
    void FetchResources(); //Fetches textures, text files
    void MakeDrawables(std::shared_ptr<Room>); //Creates all drawable objects - if drawable
                                               //objects position or size changes, below functions take 
                                               //that into account
                                               
    void RenderRoom(std::shared_ptr<Room> , bool);

    void RenderPlayer(Player& p);

    void RenderAttributes(Player& P);
    void RenderException(const std::string& str);
    void RenderPaused();
    void RenderInstructions();

    void RenderInventory(Player& P);
    void RenderDead(Player& P);
    void RenderWin(Player& P);

private:

    sf::RenderWindow& window_;
    int dungeonScreenOffset = 50;
    int dungeonScreenOffsetX = 120;
    const int columnSize = 20;
    sf::Color backgroundColor = sf::Color(100, 100 ,100);  
    sf::Color playerColor = sf::Color(30, 50, 255);
    sf::Color backgroundWcolor = sf::Color(50,50,50);
    sf::Font font;
    sf::Texture WallTexture;
    sf::Texture DoorTexture;
    sf::Texture FloorTexture;
    sf::Texture ItemTexture;
    std::vector<sf::RectangleShape > Drawables;
    std::vector<sf::RectangleShape > Doors;
    std::vector<sf::Text > Texts;
};
