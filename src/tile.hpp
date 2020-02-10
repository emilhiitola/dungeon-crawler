//class for tile
#pragma once
#include "inventory.hpp"

enum TileType {
    Wall,
    Floor,
    Door
};

class Tile {
    
    public:
        Tile(TileType type)
        :type_(type) {
            Inventory inventory_=Inventory(100);
            hasCharacter_=false;
        }

        bool IsBlocked();  //Returns True of the tile is wall or if there is another character
        void Occupy(); 
        void Unoccupy();
        void Make_Door();
        TileType GetType();
        Inventory& getInventory();
    private:
        TileType type_; //Wall or not wall
        Inventory inventory_; //tiles can have items to pick up
        bool hasCharacter_; //true if player on tile
        
    
};
