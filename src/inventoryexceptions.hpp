#pragma once

#include <exception>
#include <string>
#include "enumtypes.hpp"

class InventoryException: public std::exception{
    public:

    InventoryException(){};
    virtual const std::string GetError()const=0;
};

class CraftingException: public InventoryException{
    public:
    CraftingException(CraftableType type): InventoryException(), type_(type){}
    const std::string GetError()const{
        std::string str="You don't have enough ";
        switch (type_)
        {
        case Stone:
            str+="stone";
            break;
        
        case Wood:
            str+="wood";
            break;
        
        case Iron:
            str+="iron";
            break;
        }

        str+=",\ncrafting failed.";
        return str;
    }

    private:
    CraftableType type_;
};

class DonateException:public InventoryException{
    public:
    DonateException():InventoryException(){}
    const std::string GetError()const{
        std::string str= "Your inventory was too full, some\nof the collected items couldn't\nbe added to your inventory";
        return str;
    }
};

class CraftnullException:public InventoryException{
    public:
    CraftnullException(ItemType itype):InventoryException(), itype_(itype){}
    const std::string GetError()const{
        std::string str="You don't have ";
        switch (itype_)
        {
        case Wep:
            str+="weapon ";
            break;
        
        case Pot:
            str+="potion ";
            break;
        }
        str+="\nin your hand, crafting failed.";
        return str;
    }
    private:
    ItemType itype_;
};