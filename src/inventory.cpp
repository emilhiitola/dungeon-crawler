
#include "inventory.hpp"
#include <algorithm>
#include <sstream>


Inventory::Inventory(size_t max_size):max_size_(max_size){}

size_t Inventory::getSize(){
   //inventory size means the sum of lengths of different containers
   return craftables_.size()+weapons_.size()+potions_.size();
}   
        
const size_t& Inventory::getMaxSize()const{
    return max_size_;
}



bool Inventory::addItem(std::shared_ptr<Weapon> w){
    
    if(getSize()>=max_size_){
        
        return false;
    }
        weapons_.push_back(w);
        return true;
}
bool Inventory::addItem(std::shared_ptr<Potion> p){
    
    if(getSize()>=max_size_){
        
        return false;
    }
        potions_.push_back(p);
        return true;

}
bool Inventory::addCraftable(CraftableType type){
    for(auto c:craftables_){
        if((*c).getType()==type){
            if((*c).increaseAmount()){
                return true;
            }
        }
    }
    //checking if inventory is full:
    if(getSize()>=max_size_){
            return false;
    }
    //making new object if there is space in inventory:
    else{
            craftables_.push_back(std::make_shared<Craftable> (Craftable(type,1)));
            return true;
    }
    
}

bool Inventory::addCraftable(std::shared_ptr<Craftable> c){
    if(getSize()<max_size_){
        craftables_.push_back(c);
        organizeCraftables();
        return true;
    }
    else{
        return false;
    }
}

std::shared_ptr<Weapon> Inventory::nextWeapon(){
    if(weapons_.size()==0){
        return nullptr;
    }
    else{
        return weapons_.front();
    }
}
std::shared_ptr<Potion> Inventory::nextPotion(){
    if(potions_.size()==0){
        return nullptr;
    }
    else{
        return potions_.front();
    }
}

std::shared_ptr<Potion> Inventory::changePotion(std::shared_ptr<Potion> p){
    if(p==nullptr){
        return nextPotion();
    }
    if(p==potions_.back()){
            return potions_.front();
    }
    for(auto it=potions_.begin();it!=potions_.end();it++){
            if(*it==p){
                it++;
                return *it;
            }
    }
    return p;

}
std::shared_ptr<Weapon> Inventory::changeWeapon(std::shared_ptr<Weapon> w){
    if(w==nullptr){
        return nextWeapon();
    }
    if(w==weapons_.back()){//checking if the parameter item is the last one in the list
            return weapons_.front();//returns the first item
    }
    for(auto it=weapons_.begin();it!=weapons_.end();it++){
            if(*it==w){
                it++;
                return *it;
            }
            
    }
    return w;
    
}



void Inventory::upgrade(Item& upgreadable,bool x){
    CraftableType type=upgreadable.getCraft();

    auto it=find_if(craftables_.begin(),craftables_.end(),
                    [type](std::shared_ptr<Craftable> c)
                    {return type==c->getType(); }); 
    
    if(it==craftables_.end()){
        //if there isn't right craftable, throws exception
        throw CraftingException(upgreadable.getCraft());
    }
    else{
        if(x==1){
            upgreadable.repairItem();
        }
        else{
        upgreadable.upgradeItem();
        }
        (*it)->decreaseAmount();
        if((*it)->getAmount()==0){
            //if craftables amount gets to 0 it is deleted
            craftables_.erase(it);
        }
    }
}



void Inventory::donateInventory(Inventory& target_inventory){
    

    
 if (getSize()>0)
    {
    
    while(target_inventory.getSize() <target_inventory.getMaxSize() && getSize()>0){
    
        

        int x1=rand() % 3+1; //the order of adding different items is randomized
        int x2=rand() %2+1;
        
        switch (x1)
        {
        case 1:
        
            donateWeapon(target_inventory);
            if(x2 == 1){
                donatePotion(target_inventory);
                donateCraftable(target_inventory);
            }
            else{
                donateCraftable(target_inventory);
                donatePotion(target_inventory);
            }
            break;
        
        case 2:
        
            donatePotion(target_inventory);
            if(x2 == 1){
                donateWeapon(target_inventory);
                donateCraftable(target_inventory);
            }
            else{
                donateCraftable(target_inventory);
                donateWeapon(target_inventory);
            }
            break;

        case 3:
        
            donateCraftable(target_inventory);
            if(x2 == 1){
                donatePotion(target_inventory);
                donateWeapon(target_inventory);
            }
            else{
                donateWeapon(target_inventory);
                donatePotion(target_inventory);
            }
            break;
        }

        
    }
    //there could be still space for craftables:
    for(auto c:craftables_){
        if(target_inventory.addCraftable(c)){
            deleteCraftable(c);
        }
    }
    }
    if(getSize()>0){
        throw DonateException();
    }
    
}
void Inventory::donateWeapon(Inventory& target_inventory){
    
    if(!weapons_.empty()){
           if(target_inventory.addItem(weapons_.front())){
            deleteItem(weapons_.front());
            } 
    }
}
void Inventory::donatePotion(Inventory& target_inventory){
    
    if(!potions_.empty()){
            if(target_inventory.addItem(potions_.front())){
            deleteItem(potions_.front());
            }
    }
}
void Inventory::donateCraftable(Inventory& target_inventory){
    
    if(!craftables_.empty()){
        
            if(target_inventory.addCraftable(craftables_.front())){
                
            deleteCraftable(craftables_.front());
            }
    }
    
}


void Inventory::emptyInventory(){

    weapons_.clear();
    potions_.clear();
    craftables_.clear();
}

void Inventory::organizeCraftables(){    
    for(auto b = craftables_.begin(); b!=craftables_.end(); b++){
        for(auto e=craftables_.end()-1;e!=b;e--){
            
            if((*b)->getType()==(*e)->getType()){
                while((*b)->getAmount()!=(*b)->getMaxAmount() && (*e)->getAmount()!=0){
                    (*b)->increaseAmount();
                    (*e)->decreaseAmount();
                }
            }

            if((*e)->getAmount()==0){
                craftables_.erase(e);
            }
            
        }
    }
}

void Inventory::deleteItem(std::shared_ptr<Item> i){
    if (i->getItemType()==Pot){
        if(potions_.size()==0){
            return;
        }
        for(auto it=potions_.begin();it!=potions_.end();it++){
            if(*it==i){
                potions_.erase(it);
                break;
            }
        }
    }

    else if(i->getItemType()==Wep){
        if(weapons_.size()==0){
            return;
        }
        for(auto it=weapons_.begin();it!=weapons_.end();it++){
            if(*it==i){
                weapons_.erase(it);
                break;
            }
        }
    }

}

void Inventory::deleteCraftable(std::shared_ptr<Craftable> i){
    if(craftables_.size()==0){
        return;
    }
    for(auto it=craftables_.begin();it!=craftables_.end();it++){
        if(*it==i){
            craftables_.erase(it);
            break;
        }
    }
}
const int Inventory::countCraftabletype(CraftableType t) const{
    int counter=0;
    for(auto c:craftables_){
        if(c->getType()==t){
            counter+=c->getAmount();
        }
    }
    return counter;
}

const std::string Inventory::printCraftables()const{
    std::string str="Craftables:\n\n";
    str+="Stones: ";
    std::stringstream ss1;
    ss1<<countCraftabletype(Stone);
    str+=ss1.str();
    str+="\nWood: ";
    std::stringstream ss2;
    ss2<<countCraftabletype(Wood);
    str+=ss2.str();
    str+="\nIron: ";
    std::stringstream ss3;
    ss3<<countCraftabletype(Iron);
    str+=ss3.str();
    return str;
}

const std::string Inventory::printWeapons()const{
    std::string str="Weapons:\n\n";
    
    for (auto i:weapons_){
        str+=i->printItem();
        str+="\n";
    }
    return str;
}
const std::string Inventory::printPotions()const{
    std::string str="Potions:\n\n";

    for(auto i:potions_){
        str+=i->printItem();
        str+="\n";
    }
    return str;
}

