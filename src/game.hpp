#pragma once
#include <iostream>
#include "room.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "direction.hpp"
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "renderer.hpp"

enum GameState {
    Play,
    Paused,
    Info,
    Dead,
    Win,
    Inventory,
    Exception
};

class Game {
    private:
        bool running;
        GameState CurrentState;
        int WinScore = 1000;
        std::string ex = "I'm the exception box";
        
        void Render(sf::RenderWindow& window, Player& P, std::shared_ptr<Room> R, Renderer& ren, bool changedroom = false);
        void MonsterTurn(std::shared_ptr<Room> R);
        void Update(Player& P);
        std::shared_ptr<Room> processEvent(sf::Event& event, Player& P, std::shared_ptr<Room> R);
    public:
        Game() {}
        ~Game() {}
        void InitandRun();
};

