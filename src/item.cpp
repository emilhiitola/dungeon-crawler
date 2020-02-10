#include "item.hpp"
#include "enumtypes.hpp"

Item::Item(ItemType itype, int level) 
        : itype_(itype){
            if(level<=0){//level can only be positive
                level_=1;
            }
            else{
                level_=level;
            }
            duration_=5*level;
    }
const ItemType& Item::getItemType()const{
    return itype_;
}

const int& Item::getLevel()const{
    return level_;
}

const int& Item::getDuration()const{
    return duration_;
}


int Item::useItem(){
    return duration_-=1;
}