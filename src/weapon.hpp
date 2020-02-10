#pragma once
#include <sstream>
#include "item.hpp"
#include "enumtypes.hpp"

/* 
*There are three types of weapons, bowm axe and sword. They act different ways when player tries to hit.
*Because "hit" method is implemented in player class, the differences don't show here
*/


class Weapon: public Item{
    public:
        Weapon( WeaponType type,int level=1);
        

        const double getDamage();
        const WeaponType& getType()const;

        const CraftableType& getCraft()const;

        void repairItem();

        void upgradeItem();

        const std::string printItem()const;

    private:
        WeaponType type_;
        CraftableType craft_;
};