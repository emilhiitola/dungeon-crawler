// class for enemy monsters iherits from Character 
#include "monster.hpp"
#include "room.hpp"
#include <iostream>
#include <cmath>


Monster::Monster(int hp , int damage,std::pair<int,int> location,Player& target,std::weak_ptr<Room> room, int level)
        :target_(target), Character(hp+level*12 +level*level,damage + 2*level,location,room,level){}



    


bool Monster::turn(){


    std::pair<int,int> playerposition = target_.Getlocation();
            int dn = playerposition.first - location_.first; 
            int de = playerposition.second - location_.second; 
            
            if( abs(dn) + abs(de) ==1 ){
                hit();
            }

            else if (abs(dn) > abs(de)) {
                

                if (dn > 0){ Move(SOUTH);}
                else{ Move(NORTH); }
            }
            else if (abs(de) > abs(dn)) {

                 if (de > 0) { Move(EAST); }
                else { Move(WEST);}
            }
            else { //abs(dn) == abs(de)
               
                
                if (rand() % 10 >= 5) {
                    if (de > 0) Move(EAST);
                    else  Move(WEST);
                } 
                else {
                    if (dn > 0) Move(SOUTH);
                    else Move(NORTH);
                }
            }

            return true;




}

        void Monster::hit(){

           if( target_.loose_health(damage_)){
               target_.getRoom()->setPlayerLocation(std::make_pair(-1,-1));
            
           }
        }

