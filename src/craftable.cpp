#include "craftable.hpp"
#include "enumtypes.hpp"

Craftable::Craftable( CraftableType type, int amount, int max_amount) 
    : type_(type),max_amount_(max_amount) {
        if(amount<=0){//amount must be positive
            amount_=1;
        }
        else if(amount>max_amount_){//amount can't be bigger than max_amount
            amount_=max_amount_;
        }
        else{
            amount_=amount;
        }
    }

const CraftableType& Craftable::getType()const{
    return type_;
}

const int& Craftable::getAmount()const{
    return amount_;
}
const int& Craftable::getMaxAmount()const{
    return max_amount_;
}

bool Craftable::decreaseAmount(){
    if(amount_>0){
    amount_-=1;
    return true;
    }
    else{
        return false;
    }
}

bool Craftable::increaseAmount(){
    if(amount_<max_amount_){
        amount_++;
        return true;
    }
    else{
        return false;
    }
}