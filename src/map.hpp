#pragma once
#include <cmath>
#include <vector>
#include "room.hpp"
#include <memory>



class Map {
    public:
        //function to create a map and link all the rooms in it 
        static Map createMap(int rooms, int maxSize=10);
        
        const std::vector<std::shared_ptr<Room> > getRooms() const;

        protected:
        //constructor with amount of rooms and max size of the rooms as parameters
        Map(int rooms, int maxSize);
        
    private:
        //function to link all the rooms together
        void link();
        //vector of rooms
        std::vector<std::shared_ptr<Room> > rooms_;
    

};