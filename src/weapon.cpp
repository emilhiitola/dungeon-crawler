#include "weapon.hpp"
#include "enumtypes.hpp"

Weapon::Weapon( WeaponType type,int level) 
        :Item(Wep,level), type_(type){
             
            switch (type)
            {
            case Bow:
                craft_=Wood;
                break;
            
            case Axe:
                craft_=Iron;
                break;
            case Sword:
                craft_=Stone;
                break;
            }

        }
const double Weapon::getDamage() {
    if(type_==Sword) return 8*level_;
    return level_*5;
}

const WeaponType& Weapon::getType()const{
    return type_;
}

const CraftableType& Weapon::getCraft()const{
    return craft_;
}

void Weapon::repairItem(){
    duration_=level_*5;
}

void Weapon::upgradeItem(){
    level_++;
    duration_+=5;
}

const std::string Weapon::printItem()const{
    std::string str;
    switch (type_)
    {
    case Bow:
        str+="Bow\n";
        break;
    
    case Axe:
        str+="Axe\n";
        break;
    case Sword:
        str+="Sword\n";
        break;
    default:
        str+="no weapon\n";
        return str;
        break;
    }
    str+="Level: ";
    std::stringstream ss;
    ss<<getLevel();
    str+=ss.str();
    str+="\nUses left: ";
    std::stringstream ss2;
    ss2<<getDuration();
    str+=ss2.str();
    str+="\n";
    return str;
}    