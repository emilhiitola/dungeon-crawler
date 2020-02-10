
//The Character-class is an abstract base class for Monsters and the Player.



 #pragma once
 #include <list>
 #include <vector>
 #include "inventory.hpp"
 #include "direction.hpp"
 #include <cmath>
 #include <memory>
 
class Room;



class Character {

        public:

                Character(int hp , int damage,std::pair<int,int> location,std::weak_ptr<Room> room,int level=1);
                
        
                Inventory& getInventory();                                      //returns inventory_
                const int& getHP()const;                                        //returns HP_
                const int& getLevel()const;                                     // returns level_
                const int& getDamage()const;                                    // returs damage_
                const std::pair<int,int>& Getlocation() const;                  // returns location_
                DirectionType getFacing() const;

                //Prints location x y to standard output, only for debugging 
                const void printLoc() const;


                /*Move:checks if movement of steps(=default 1) in direction is possible
                and moves the character returns true if the character moved succesfully false otherwise*/

                bool Move(DirectionType direction,int steps = 1); 

                /* turn,movementdirection and hit:
                * pure virtual function subclasses defines the function
                */
                
                virtual bool turn() =0;   
                virtual void hit() =0;  

                /* takes Damage taken as parameter and subtracts the DMG from HP_
                * function also checks if health is  below 0 the Character dies and the object is deleted. 
                * returns true if character dies false othewise
                */
                bool loose_health(int DMG);

                
        protected:
                int HP_;
                int  damage_ ;
                int level_ ;
                std::pair<int, int> location_ ;
                Inventory inventory_;
                std::weak_ptr<Room> room_;
                DirectionType facing;
                

                

 };
 
