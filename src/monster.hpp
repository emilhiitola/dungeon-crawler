// class for enemy monsters iherits from Character
#pragma once
#include "character.hpp"
#include "player.hpp"

class Monster : public Character{
    public:

        Monster(int hp , int damage,std::pair<int,int> location,Player& target,std::weak_ptr<Room> room, int level=1);
        

        /*MovememtDirection: function that takes no parameters and returns nothing
        and does not exsist*/
        

        /* turn: takes no parameters and returns nothing. function does everything that monster does
        * on its turn.  Moves towards the player or hits the player if adjecent to player.
        */ 
        bool turn();
        /* hit: takes no parameters and returns nothing. Monster tries to hit player*/
        void hit();

    private: 
        Player& target_;
        
};
