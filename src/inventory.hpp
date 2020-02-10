/*
Inventory class
    this class handles crafting, upgrading, repairing and the usage of items 
    for the player

basic attributes:
    containers for different items
*/

#pragma once
#include <vector>
#include "potion.hpp"
#include "weapon.hpp"
#include "craftable.hpp"
#include "inventoryexceptions.hpp"
#include <iostream>
#include <memory>


class Inventory{
    public:
        explicit Inventory(size_t max_size=10);

        /*getSize returns conatiner's  current size*/
        size_t getSize();

        const size_t& getMaxSize()const;

        /* addItem takes a pointer to an item as a parameter
        * and adds it to the right container
        */
       
       // bool addItem(std::shared_ptr<Item>);
         bool addItem(std::shared_ptr<Potion>);
        bool addItem(std::shared_ptr<Weapon>);
    
        

        /* addCraftable: overloaded function that takes either type of the craftable
        * or pointer to craftable as a parameter. Returns true if adding was succesful and false if it was not
        * (eg. inventory was full)
        */ 
        bool addCraftable(CraftableType type);
        bool addCraftable(std::shared_ptr<Craftable> Craftable);

        /* nextweapon returns pointer to the first weapon on the weapons vector.
        * if weapons_ is empty, returns null
        */ 

        std::shared_ptr<Weapon> nextWeapon();
        /* nextPotion works similarly as nextweapon */

        std::shared_ptr<Potion> nextPotion();
        
        /* changeItem:
        * takes as a parameter the item player currently has on hand
        * returns the item that is next in the corresponding vector
        * (same item type than the parameter has),
        * if vector contains only the current item, does nothing and returns
        * the item given as a parameter.
        */

        std::shared_ptr<Potion> changePotion(std::shared_ptr<Potion>);
        std::shared_ptr<Weapon> changeWeapon(std::shared_ptr<Weapon>);




        /* upgrade:
        * takes  reference to a weapon or potion as a parameter and also a bool, which tells whether the item should be upgraded or repaired.
        *if x==1, repairs else upgrades.
        * returns true if upgrading succeed, else return false.
        */

       void upgrade(Item& upgreadable,bool x);
       
        /*donateInventory:
        * Takes another inventory as a parameter, where items from the current inventory are moved.
        * Function checks whether there is something in the target inventory or not:
        * If target inventory is empty, copy assignment is used and after that the donator inventory is emptied. 
        * If there already is something, items are moved one by one from inventory to another until
        * the target inventory is full.
        * Returns the target inventory.
        */

        void donateInventory(Inventory& target_inventory);

        //helper functions for donateInventory:
        void donateWeapon(Inventory& target_inventory);
        void donatePotion(Inventory& target_inventory);
        void donateCraftable(Inventory& target_inventory);
        
        /*emptyInventory:
        * function that is used in donateInventory, works like destructor but doesn't delete the inventory itself
        */

        void emptyInventory(); 

        /*organizeCraftables:
        * Function that organizes craftables.
        * Because craftables are in stacks and it is possible that there
        * are multiple unfull stacks of same type of craftable.
        * This function organizes those so, that as many stacks as possible are full
        * Takes no parameters and returns nothing.
        */ 

        void organizeCraftables();

        /* deleteItem: function for deleting item from inventory
        * takes pointer to an item as a parameter and returns nothing
        */

        void deleteItem(std::shared_ptr<Item>);
        /*deleteCraftable: same as deleteItem but for craftables*/

        void deleteCraftable(std::shared_ptr<Craftable>); 
        

        /*countCraftabletype:
        * function that takes craftable type as a parameter and returns how many craftables of that type
        * there are in inventory
        */ 
        const int countCraftabletype(CraftableType t) const;

        /*printCraftables:
        * returns string that contains amounts of different types of craftables
        */ 
        const std::string printCraftables()const;
        const std::string printWeapons()const;
        const std::string printPotions()const;

        /*levelUP:
        * adds 5 to max_size
        */
        void levelUp(){
            max_size_+=5;
        }

    private:
        size_t max_size_=15;
        std::vector<std::shared_ptr<Potion>> potions_;
        std::vector<std::shared_ptr<Weapon>> weapons_;
        std::vector<std::shared_ptr<Craftable>> craftables_;

};