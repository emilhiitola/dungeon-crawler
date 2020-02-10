#pragma once
#include "enumtypes.hpp"


class Craftable{
    public:
   
   
        Craftable( CraftableType type, int amount, int max_amount=5);

        const CraftableType& getType()const;

        const int& getAmount()const;
        const int& getMaxAmount()const;
        //decraseAmount decrases the amount by one and returns the amount after operation
        bool decreaseAmount();
        //increaseAmount increases the amount by one. If amount_==max_amount_ already, return false.
        bool increaseAmount();


    private:
        CraftableType type_;
        int amount_;
        int max_amount_=5;
};
