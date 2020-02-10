#include "tile.hpp"


bool Tile::IsBlocked() {
    if (type_ == Wall) {
        return true;
    }
    if (type_ ==Door){
        return false;
    }
    if (hasCharacter_ == true) {
        return true;
    }
    return false;
}

void Tile::Make_Door() {type_ = Door;}

void Tile::Occupy() {
    hasCharacter_ = true;
}

void Tile::Unoccupy() {
     hasCharacter_ = false;
}

TileType Tile::GetType() {return type_;}

Inventory& Tile::getInventory(){
    return inventory_;
}
