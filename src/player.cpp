
//    Player class


#include <iostream>
#include "SFML/Graphics.hpp"
#include "player.hpp"
#include "room.hpp"
#include "monster.hpp"
#include "enumtypes.hpp"

std::map< DirectionType,std::pair<int,int> > directionsMap{
                        { NORTH,std::make_pair(-1,0) } ,
                        { SOUTH , std::make_pair(1,0) } ,
                        { WEST , std::make_pair(0,-1) } ,
                        { EAST , std::make_pair(0,1) }
                };



Player::Player(int hp , int damage,std::pair<int,int> location, std::weak_ptr<Room> room, int level)
        : maxHP_(hp), Character(hp,damage,location,room,level), activePotion_(nullptr), potion_(nullptr), weapon_(nullptr) { levelupXP=50; XP_=0;}

void Player::heal(int healingPoints) {
    if(HP_ + healingPoints < maxHP_){
        HP_ += healingPoints;
    }else{
        HP_ = maxHP_;
    }
    
}
void Player::hit() {//looks like a disaster
    
    auto room = room_.lock();
    
    WeaponType wtype= Sword;
    int dmg = damage_;
    if (weapon_) {
        wtype = weapon_->getType();
        dmg = damage_ + weapon_->getDamage();
        weapon_->useItem();
        //if weapons duration after this turn is 0, it is erased from inventory and equipped weapon is set to nullptr
        if(weapon_->getDuration()==0){
            inventory_.deleteItem(weapon_);
            
            weapon_=nullptr;
        }
    }
    std::list< std::shared_ptr<Monster> > killed;
    switch(wtype) {
        case Bow:
            
            if(abs(directionsMap[facing].first)==1){
                for (auto it : room->getMonsters()) {
                        if (it->Getlocation().second == location_.second && abs(location_.first + directionsMap[facing].first
                             - it->Getlocation().first) < abs(location_.first - it->Getlocation().first) )  
                        {
                            if(it->loose_health(dmg)){ earnXP(it->getLevel()); 
                            killed.push_back(it);
                            }
                        }
                    }
            }else {
                for (auto it : room->getMonsters()) {
                        if (it->Getlocation().first == location_.first && abs(location_.second + directionsMap[facing].second
                            - it->Getlocation().second) < abs(location_.second - it->Getlocation().second) ) 
                        {
                            if(it->loose_health(dmg)){ earnXP(it->getLevel()); 
                            killed.push_back(it);
                            }
                        }
                    }
            }
            break;
        case Axe:
                //std::cout << "Axe even angels will fall" <<std::endl;
            for (auto it : room->getMonsters()) {
                if (abs(it->Getlocation().first - location_.first) <= 1 && abs(it->Getlocation().second - location_.second) <= 1) {
                    if(it->loose_health(dmg)){ earnXP(it->getLevel());
                    killed.push_back(it);
                    }
                }
            }
            break;
        default:
            for (auto it : room->getMonsters()) {
                        if (it->Getlocation() == std::make_pair(location_.first +
                            directionsMap[facing].first,location_.second +directionsMap[facing].second))
                             {
                                if(it->loose_health(dmg)){ earnXP(it->getLevel());
                                killed.push_back(it);}
                        }
                }

            
    }

    for (auto kill : killed){
        room->getMonsters().remove(kill);
    }


}
void Player::earnXP(int monsterlvl){
    XP_ += monsterlvl*5;
    score_ += XP_;
    if(XP_> levelupXP){
        level_++;
        XP_ = XP_ - levelupXP;
        
        levelupXP =(int) round(levelupXP*1.5);
        maxHP_+=20;
        damage_+=2;
        HP_=maxHP_;
        inventory_.levelUp();
    }
}


const int Player::getScore() const{
    return score_;
}
bool Player::turn(){   //implementation of turn 
   
    if(activePotion_){
        auto ty = activePotion_->getType();
        switch (ty)
        {
        case Health:
            heal(activePotion_->getLevel()*10);
            activePotion_->useItem();

            if(activePotion_->getDuration()<=0){  
                inventory_.deleteItem(activePotion_);
                activePotion_=nullptr;
            } 
            break;

        case Turn: 
            activePotion_->useItem();
           
            if(activePotion_->getDuration()<=0){
                 inventory_.deleteItem(activePotion_);
                 activePotion_=nullptr;
            }
            return true;
            break;

        case Attack:
            damage_ += 2*activePotion_->getLevel();
            activePotion_->useItem();
           
            if(activePotion_->getDuration()<=0){
                damage_ -= 2*activePotion_->getLevel();
                inventory_.deleteItem(activePotion_);
                activePotion_=nullptr;
            }
            break;
        }
       
    }
    return false;
    
}
void Player::changeWeapon(){
    weapon_ = inventory_.changeWeapon(weapon_);
}

void Player::usePotion(){
    //current potion is set to active potion
    activePotion_ = potion_;
    //std::cout << "using potion" << std::endl;
    //current potion is set to next potion from active potion
    potion_ =(std::shared_ptr<Potion>) inventory_.changePotion(activePotion_);
    if(activePotion_==potion_){
        //if active potion and current potion refers to same item, potion is set to nullptr
        potion_=nullptr;
    }

}

void Player::changePotion() {
    potion_ = inventory_.changePotion(potion_);
}

void Player::upgradeWeapon(bool x){
    if(weapon_==nullptr){
        throw CraftnullException(Wep);
    }
    
    inventory_.upgrade(*weapon_,x);
}
void Player::upgradePotion(){
    if(potion_==nullptr){
        throw CraftnullException(Pot);
    }
    inventory_.upgrade(*potion_,0);
}

const int& Player::getMaxHP() const {
    return maxHP_;
}
const int& Player::getLvlXP() const {
    return levelupXP;
}

const int& Player::getXP() const{
    return XP_;
}

std::shared_ptr<Room> Player::getRoom(){
    return room_.lock();
}
bool Player::MoveR(DirectionType direction ,int steps){
    auto room = getRoom();
    if(Move(direction , steps)){
        room->setPlayerLocation(location_); // change rooms attribute so player is rendered correctly
        for ( auto d : room->getDoors() ){    /// check if player is on a door
            if (location_.first == std::get<2>(d).first && location_.second == std::get<2>(d).second ){
                
                room_=std::get<0>(d);
                room = room_.lock();
                location_.first = 2;       // player location set to coordinate most up and left
                location_.second = 2;
               // std::cout << room->getNumber() << std::endl; //debugging purposes
                
                //initialize randomly 1 to 5 monsters to room if empty of monsters
                if(room->getMonsters().size() ==0 ){

                    srand(time(NULL));
                    int amount = rand() % 5 +1;
                    int height = room->getHeight();
                    int width = room->getWidth();
                    unsigned int i=0;

                    while(i<amount){
                        int y = rand() % (height-1) +3;
                        int x = rand() % (width) +2;
                        room->AddMonster(y,x,*this);
                        room->GetTiles()[y][x].Occupy();
                        i++;
                    }
                }
                return true;
            }
            
        }
    }
    
    return false;
    

}
std::shared_ptr<Weapon> Player::getWeapon() {
            return weapon_;
        }
std::shared_ptr<Potion> Player::getPotion() {
            return potion_;
        }

const std::string Player::printWeapon()const{
    std::string str="Weapon: ";
    if(weapon_==nullptr){
        return str+"None";
    }
    return str+weapon_->printItem();
}

const std::string Player::printPotion()const{
    std::string str="Potion: ";
    if(potion_==nullptr){
        return str+"None";
    }
    return str+ potion_->printItem();
}

const std::string Player::printAPotion()const{
    std::string str="Active potion: ";
    if(activePotion_==nullptr){
        return str+"None";
    }
    return str+activePotion_->printItem();
}


void Player::deleteItem(ItemType i){
    if(i==Pot){
        if(potion_){
            inventory_.deleteItem(potion_);
            potion_=nullptr;
            changePotion();
        }
        else{
            return;
        }
    }
    else if(i==Wep) {
        if(weapon_){
        inventory_.deleteItem(weapon_);
        weapon_=nullptr;
        changeWeapon();
        }
        else{
            return;
        }
    }

    
}