
#include "room.hpp"
#include <iostream>
#include "player.hpp"
#include "monster.hpp"


//creates a height*width room with and adds a player
Room::Room(  int height, int width,int num) {  // add comments
    num_=num;
    playerlocation_ = std::make_pair(2,2);
    std::vector<Tile> topline;
    std::vector<Tile> bottomline;
    std::vector<Tile> normalline;

    Tile w = Tile(Wall);
    Tile f = Tile(Floor);

    for (int i = 0; i < 2; i++) {
        topline.push_back(w);
        bottomline.push_back(w);
        normalline.push_back(w);
    }
    for (int k = 0; k < width; k++) {
        topline.push_back(w);
        bottomline.push_back(w);
        normalline.push_back(f);
    }

    for (int i = 0; i < 2; i++) {
        topline.push_back(w);
        bottomline.push_back(w);
        normalline.push_back(w);
    }
    tiles_.push_back(bottomline);
    tiles_.push_back(bottomline);

    for (int i = 0; i < height; i++) {
        tiles_.push_back(normalline);
    }

    tiles_.push_back(topline);
    tiles_.push_back(topline);

    height_ = height;
    width_ = width;
}
        


const int Room::getNumber() const{
    return num_;
}


bool Contains(const std::list<DirectionType>& l, DirectionType t) { //helper function
    for ( auto dir : l) {
        if(dir == t ) return true;
    }
     return false;
}
//adds a link to another room on one of the four walls
void Room::CreateLink(std::shared_ptr<Room> room) {
    std::list<DirectionType> existingdirections;
    for (int i = 0; i < doors_.size(); i++) {
        existingdirections.push_back( std::get<1>(doors_[i]) );
    }
    std::pair<int,int> location;
    if (!Contains(existingdirections,WEST)) {
        doors_.push_back(std::make_tuple(room,WEST,std::make_pair(height_/2+2,1)));
        tiles_[height_/2+2][1].Make_Door();
    }
    else if (!Contains(existingdirections,EAST)) {
        doors_.push_back(std::make_tuple(room,EAST,std::make_pair(height_/2+2,width_+2)));
        tiles_[height_/2+2][width_+2].Make_Door();
    }
    else if (!Contains(existingdirections,NORTH)) {
        doors_.push_back(std::make_tuple(room,NORTH,std::make_pair(1,width_/2+2)));
        tiles_[1][width_/2+2].Make_Door();
    }
    else if (!Contains(existingdirections, SOUTH)) {
        doors_.push_back(std::make_tuple(room,SOUTH,std::make_pair(height_+2,width_/2+2)));
        tiles_[height_+2][width_/2+2].Make_Door();
    }
}

std::list< std::shared_ptr<Monster> >& Room::getMonsters() {
    return monsters_;
}
std::vector<std::vector<Tile> >& Room::GetTiles() {
    return tiles_;
}

    //probability functions
    bool third(int arg){return arg % 100 < 33;}
    bool tenth(int arg){return arg % 100 < 10;} 
    bool half(int arg){return arg  % 100 < 50;}
    bool bItem(int arg){ return arg % 100 < 15;}
    bool doWeap(int arg,int arg1,int arg2){return half(arg) && half(arg1) && tenth(arg2);}


void Room::AddMonster(int y,int x ,Player& player) {

    srand(time(NULL) + y+x);


    int lvl= std::max(1,player.getLevel()-2 + rand() % 6 );
    int attackHealth = rand() % 6 +1;
    int bhp = 40 * attackHealth;
    int bap = 2 * (5-attackHealth) ;
    
    std::shared_ptr<Monster> m = std::make_shared<Monster>( Monster(bhp,bap,std::make_pair(y,x),player, shared_from_this() ,lvl) );
    
      

    //adding ramdom items randomly to the monster
    
   int prob = std::min(lvl,4);
    for ( int i = 0; i < prob; i++){  // randomization is not wörking randomly but initilizion works
        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Weapon>( Weapon(Axe,lvl))); }  //7.3 % chance to get at least a weapon
        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Weapon> (Weapon(Bow,lvl))); }
        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Weapon>( Weapon(Sword,lvl))); }

        if(half(rand())){ m->getInventory().addCraftable(Wood); }            //87.5% chance to get at least one
        if(half(rand())){ m->getInventory().addCraftable(Iron); }
        if(half(rand())){ m->getInventory().addCraftable(Stone); }

        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Potion>( Potion(Health,lvl)));}
        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Potion>( Potion(Turn,lvl)));}
        if(bItem(rand())){ m->getInventory().addItem( std::make_shared<Potion>( Potion(Attack,lvl)));}

        
    }
    monsters_.push_back(m); 
}

const int Room::getHeight() const {
    return height_;
}

const int Room::getWidth() const {

    return width_;
}

void Room::Render(sf::RenderWindow& window) {
        sf::RectangleShape backgroundW(sf::Vector2f((4+width_)*columnSize,(4+height_)*columnSize));
        backgroundW.setPosition(dungeonScreenOffset, dungeonScreenOffset);
        backgroundW.setFillColor(sf::Color(50,50,50));
        window.draw(backgroundW);
                    
        sf::RectangleShape background(sf::Vector2f(width_*columnSize,height_*columnSize));
        background.setPosition(dungeonScreenOffset+2*columnSize, dungeonScreenOffset+2*columnSize);
        background.setFillColor(backgroundColor);
        window.draw(background);

        sf::RectangleShape player(sf::Vector2f((float) columnSize, (float) columnSize));
        player.setPosition(dungeonScreenOffset+playerlocation_.second*columnSize, dungeonScreenOffset+playerlocation_.first*columnSize);
        player.setFillColor(playerColor);
        window.draw(player);

        sf::RectangleShape enemyRect(sf::Vector2f((float) columnSize, (float) columnSize));
        enemyRect.setFillColor(sf::Color(255,0,0));
        for (auto it : monsters_) {
            enemyRect.setPosition(dungeonScreenOffset+it->Getlocation().second*columnSize, dungeonScreenOffset+it->Getlocation().first*columnSize);

            window.draw(enemyRect);
        }

        sf::RectangleShape door(sf::Vector2f((float) columnSize, (float) columnSize));
        door.setFillColor(sf::Color(255,166,0));
        for (unsigned int i = 0; i<height_+4;i++){
            for(unsigned int j = 0; j<width_+4;j++){
                if(tiles_[i][j].GetType() == Door){
                    door.setPosition( dungeonScreenOffset+j*columnSize,dungeonScreenOffset+i*columnSize);
                    window.draw(door);
                }
            }
        }
        

}
std::pair<int,int> Room::GetPlayerLocation() const {
    return playerlocation_;
}
void Room::setPlayerLocation(std::pair<int,int> location) {
    playerlocation_= location;
}

const std::vector<std::tuple< std::weak_ptr<Room>, DirectionType ,std::pair<int,int> > > Room::getDoors() const {
    return doors_ ;
}