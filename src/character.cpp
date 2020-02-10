#include "character.hpp"
#include "room.hpp"
#include <iostream>
std::map< DirectionType,std::pair<int,int> > directionsMapC{
                        { NORTH,std::make_pair(-1,0) } ,
                        { SOUTH , std::make_pair(1,0) } ,
                        { WEST , std::make_pair(0,-1) } ,
                        { EAST , std::make_pair(0,1) }
                };




Character::Character(int hp , int damage,std::pair<int,int> location,std::weak_ptr<Room> room,int level):
        HP_(hp), damage_(damage), location_(location), room_(room),level_(level) {
                Inventory inventory_= Inventory();}


bool Character::Move(DirectionType direction ,int steps) {  
        std::pair<int,int> loc = location_;
        auto room = room_.lock();
        facing = direction;
        if (room->GetTiles()[loc.first+directionsMapC[facing].first*steps][loc.second + directionsMapC[facing].second*steps].IsBlocked()) {
                return false;}
        else {location_ = std::make_pair(loc.first+directionsMapC[facing].first*steps,
                                loc.second + directionsMapC[facing].second*steps);
        }

        
        room->GetTiles()[loc.first][loc.second].Unoccupy();                     
        room->GetTiles()[location_.first][location_.second].Occupy();

        //take all items from tiles inventory to characters inventory if there is enough space
        room->GetTiles()[location_.first][location_.second].getInventory().donateInventory(inventory_  );
        
        return true;
}

const void Character::printLoc() const{
        std::cout<< location_.first << "  " << location_.second<< std::endl;
}

const std::pair<int,int>& Character::Getlocation() const {
        return location_;
}

const int& Character::getHP()const{
        return HP_;
}

const int& Character::getLevel()const{
        return level_;
}

const int& Character::getDamage()const{
        return damage_;
}

bool Character::loose_health(int DMG){
        HP_ -= DMG;
        if(HP_<0){
                room_.lock()->GetTiles()[location_.first][location_.second].Unoccupy();

                try {
                inventory_.donateInventory(  room_.lock()->GetTiles()[location_.first][location_.second].getInventory());
                }
                catch(...) {
                        // catches exception if inventory of the tile is full and character dies
                }
                return true;
        }else{
                        return false;
        }
}
DirectionType Character::getFacing() const {
        return facing;
}

        Inventory& Character::getInventory() {
        return inventory_;
}
