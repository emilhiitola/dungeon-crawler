#pragma once
#include <sstream>
#include "item.hpp"
#include "enumtypes.hpp"



class Potion : public Item {
    public:
   
   
        Potion( PotionType type, int level=1); 


        const PotionType& getType()const;

        const CraftableType& getCraft()const;

        void upgradeItem();
    
        /*printPotion:
        *returns string, that has the basic information of potion. 
        */  
        const std::string printItem()const;
        void repairItem();

    private:
        PotionType type_;
        CraftableType craft_=Wood;
};