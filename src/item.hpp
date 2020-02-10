// header file for items 


#pragma once
#include <string>
#include "enumtypes.hpp"
 


class Item {
    public:
        Item(ItemType itype, int level);
        
        const ItemType& getItemType()const;

        const int& getLevel()const;

        const int& getDuration()const;

        //useItem decreases the duration by one and returns the duration that is left
        int useItem();
        
        virtual const CraftableType& getCraft()const=0;
        virtual void upgradeItem()=0;
        virtual void repairItem()=0;
        virtual const std::string printItem()const=0;

    protected:

        ItemType itype_;
        int level_;
        int duration_=5;//describes how long item can be used before it breaks/ends
};

