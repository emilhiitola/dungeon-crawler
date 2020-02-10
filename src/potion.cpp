#include "potion.hpp"
#include "enumtypes.hpp"

Potion::Potion( PotionType type, int level) 
    : Item(Pot ,level), type_(type) { 

        switch (type)
        {
        case Health:
            craft_=Wood;
            break;
        
        case Turn:
            craft_=Iron;
            duration_=level*2;
            break;
        case Attack:
            craft_=Stone;
            break;
        }
    }
    
const PotionType& Potion::getType()const{
        return type_;
    }

const CraftableType& Potion::getCraft()const{
    return craft_;
}

void Potion::upgradeItem(){
    level_++;
    switch (type_)
    {
    case Turn:
        duration_+=2;
        break;
    
    default:
        duration_+=5;
        break;
    }
    
}

const std::string Potion::printItem()const{
    std::string str;
    
    switch (type_)
    {
    case Health:
        str+="Health\n";
        break;
    
    case Turn:
        str+="Turn\n";
        break;
    case Attack:
        str+="Attack\n";
        break;
    default:
        str+="no potion\n";
        return str;
        break;
    }
    str+="Level: ";
    std::stringstream ss;
    ss<<getLevel();
    str+=ss.str();
    str+="\nDuration left: ";
    std::stringstream ss2;
    ss2<<getDuration();
    str+=ss2.str();
    str+="\n";
    return str;
}

void Potion::repairItem(){return;}