#include "map.hpp"
#include <iostream>
#include <ctime>

Map Map::createMap(int rooms, int maxSize){ // rooms = amount of rooms in the map maxSize = maxSize for rooms
     Map map = Map(rooms, maxSize); 
     map.link();
     return map;
}

Map::Map(int rooms, int maxSize){
    srand(time(NULL));
    for (int i = 0; i<rooms; i++){
        
        int height = std::min(rand() % maxSize + 5,19);      // creating random dimension rooms ( max 19 so it can be rendered )
        int width = rand() % maxSize + 5;       // between maxSize (default 10*10) and 5*5
        rooms_.push_back(std::make_shared<Room>( Room(height ,width,i)));
        
    }
}

void Map::link() {      // links rooms to each other to form the map
    size_t n = rooms_.size(); 
    if ( n <2) { return ;} // if 1 or 0 room there is nothing to link
    else if ( n ==2) { 
        rooms_[0]->CreateLink(rooms_[1]);
        rooms_[1]->CreateLink(rooms_[0]);
        return;
    }
    //std::cout << "linking first 60%"<<std::endl;
       
    int nextR = (int) std::round(n*0.6);
    for ( int i = 0; i < nextR -1; i++){       // links first 60% of the rooms, every room is linked  
        rooms_[i]->CreateLink(rooms_[i+1]);     // with the rooms next to it (in rooms_)
        rooms_[i+1]->CreateLink(rooms_[i]);

    }
    rooms_[0]->CreateLink(rooms_[nextR-1]);       // links the first and the last of the 60%
    rooms_[nextR]->CreateLink(rooms_[0]);
    //std::cout << "linking first and last of 60%"<<std::endl;
    auto linkages = std::vector<int>(n,2);

    for ( int i = nextR; i<n; i++ ){           // links the rest of the rooms to a random
        int linkTo = rand() % nextR;           // room of the first 60% 
        while( linkages[linkTo] == 4 || i == linkTo){         // max 4 links from a room to others 
            
            linkTo = rand() % nextR;
        }
        rooms_[i]->CreateLink(rooms_[linkTo]);
        rooms_[linkTo]->CreateLink(rooms_[i]);
        linkages[i]+=1;
        linkages[linkTo]+=1;
    
    }




}

const std::vector<std::shared_ptr<Room> > Map::getRooms() const {
    return rooms_;
}
    

 

