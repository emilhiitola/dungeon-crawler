 
//Class for player(s)

#pragma once
#include "character.hpp"
#include <iostream>
#include <cmath>

class Player : public Character {

    public:
        Player(int hp , int damage,std::pair<int,int> location,std::weak_ptr<Room> room, int level=1);
        


        //adds healingPoints to hp, hp can not get above maxHP
        void heal(int healingPoints);

        /* earnXP:
        * adds monsterlvl*5 to XP  and levelups if neccessary and puts new levelupXp
        *  this function is called every time a monster is killed
        */
        void earnXP(int monsterlvl);               


       /* hits in the facing direction with weapon if equipped
        If there is a monster in range of the weapon the monster 
        looses health. Uses one duration of the weapon
       */
        void hit();

        /* MoveR check if player moves in to a door tile if not 
        uses regular character move 
        If player enters a new room without any monster calls the rooms
        add monster 1 to 5 times
        */
        bool MoveR(DirectionType direction ,int steps =1);

        // checks if player has an active potion and uses one duration of it
        bool turn();


        
        // adds the weapon to players inventory
        void addWeapon( std::shared_ptr<Weapon> weapon);

        //changes weapon to the next in inventory
        void changeWeapon();

        // changes potion to the next in inventory
        void changePotion();

        
        //uses the currently equipped potion and eqquips the next potion
        void usePotion();
           
        // if x==0 upgrades the equipped weapon (weapon lelevup) if x==1 repaires the weapon
        void upgradeWeapon(bool x);
        // upgrades the eqquipped potion
        void upgradePotion();
        
        void deleteItem(ItemType i);
        // lots of nice getter functions and an awesome joke to make the programmer happy
        std::shared_ptr<Room> getRoom(); 
        const int& getMaxHP()const; //constit on monet sanoi cpp ohjelmoija(eli ne puuttu näist kaikist :D)   XD lisää näitä!!
        const int& getLvlXP()const;
        const int& getXP()const;
        const int getScore() const;
        
        std::shared_ptr<Weapon> getWeapon();
        std::shared_ptr<Potion> getPotion();
        //functions that return string, that renderer can use
        const std::string printWeapon()const;
        const std::string printPotion()const;
        const std::string printAPotion()const;
        

    private:
        int XP_;
        int maxHP_; 
        int levelupXP;          // xp required for next level
        int score_=0;
        std::shared_ptr<Weapon> weapon_;         // eqquipped  weapon
        std::shared_ptr<Potion> potion_;         // eqquipped potion
        std::shared_ptr<Potion> activePotion_;  //potion that is used, this is checked on every turn until the potions duration is 0        

        
};