/* Class for rooms 
A 2D-vector of Tile-objects

[1][0]|[1][1]
______|________
[0][0]| [0][1]

etc.
*/
#pragma once
#include "tile.hpp"

#include <list>
#include <tuple>
#include <vector>
#include "direction.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime>


class Player;
class Monster;
class Room : public std::enable_shared_from_this<Room>{
    protected:
        const int columnSize = 20;
        const int dungeonScreenOffset = 40;
        sf::Color backgroundColor = sf::Color(100,100,100);
        sf::Color playerColor = sf::Color(30, 50, 255);
        std::vector<std::vector<Tile> > tiles_; //2D-vector of tiles
        std::list< std::shared_ptr<Monster> > monsters_;  //monsters located in the room
        std::vector<std::tuple< std::weak_ptr<Room>, DirectionType ,std::pair<int,int> > > doors_;
        
        std::pair<int,int> playerlocation_;
        
        int height_;
        int width_;
        int num_;
    public:
        //Constructor: creates x * y Room
        Room( int height,int width,int num);
        const int getNumber() const;
        
        
        //returns list of monster positions (used by move-function in monster)
        const std::list<std::pair<int,int> > getMonsterPositions() const;
        const std::vector<std::tuple< std::weak_ptr<Room>, DirectionType ,std::pair<int,int> > > getDoors() const;
        std::list< std::shared_ptr<Monster> >& getMonsters();
        std::vector<std::vector<Tile> >& GetTiles();

        const int getHeight() const;
        const int getWidth() const;
        void AddMonster(int y,int x ,Player& player);
        void tostring();
        void CreateLink( std::shared_ptr<Room>);
        void Render(sf::RenderWindow &W);
        //bool MovePlayer(DirectionType direction, int steps = 1);
        std::pair<int,int> GetPlayerLocation() const;
        void setPlayerLocation(std::pair<int,int> location);
};