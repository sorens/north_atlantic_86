//
//  game.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/11/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "game.hpp"
#include <iostream>     // TODO inject

#pragma mark _Game

class _Game : public Game
{
public:
    _Game()
    {
    }
    
    void add_nato_player(const std::string &name) override
    {
        _player_nato = Player::factory(Alliance::NATO, name);
    }
    
    void add_soviet_player(const std::string &name) override
    {
        _player_soviet = Player::factory(Alliance::SOVIET, name);
    }
    
    std::string current_time() override
    {
        // TODO convert _current_turn into a human-readable string
        return "";
    }
    
    int current_turn() override
    {
        return _current_turn;
    }
    
    void display_map() override
    {
        // TODO inject std::cout
        
        std::cout << "NATO:     " << _player_nato->name() << std::endl;
        std::cout << "SOVIET:   " << _player_soviet->name() << std::endl;
        std::cout << "======= MAP =======" << std::endl;
        auto grid = _map->grid();
        auto size = grid.size();
        int side = std::pow(size, 0.5);
        
        int i = 0;
        for (auto g : grid) {
            switch (g->type()) {
                case GridType::Landmass:
                    std::cout << "*";
                    break;
                case GridType::Ocean:
                    std::cout << "_";
                    break;
                case GridType::Airbase:
                case GridType::Port:
                    std::cout << g->name()[0];
                    break;
                case GridType::Unknown:
                    break;
            }
                    
            std::cout << " ";
            
            ++i;
            if (i % side == 0) {
                i = 0;
                std::cout << std::endl;
            }
        }
                    
        std::cout << "===================" << std::endl;
    }
    
    void display_weather() override
    {
        // TODO inject std::cout

        std::cout << "** WEATHER **" << std::endl;
        
        auto grid = _map->grid();
        auto size = grid.size();
        int side = std::pow(size, 0.5);
        int i = 0;
        for (auto g : grid) {
            auto weather = g->weather();
            int type = static_cast<int>(weather->type());
            if (type < 10)
                std::cout << type;
            else if (type == 10)
                std::cout << "A";
            else if (type == 11)
                std::cout << "B";
            else if (type == 12)
                std::cout << "C";
            else
                std::cout << "?";
            std::cout << " ";
            
            ++i;
            if (i % side == 0) {
                i = 0;
                std::cout << std::endl;
            }
        }
        std::cout << "*************" << std::endl;
    }
    
    void initialize(std::vector<std::shared_ptr<MapSetup>> map_data)
    {
        _map = Map::factory(map_data);
    }
    
    std::shared_ptr<Map> map() override
    {
        return _map;
    }
    
    void next_turn() override
    {
        // TODO implemenent
    }
    
    std::shared_ptr<Player> player_nato() override
    {
        return _player_nato;
    }

    std::shared_ptr<Player> player_soviet() override
    {
        return _player_soviet;
    }

private:
    std::shared_ptr<Map> _map;
    int _current_turn;
    std::shared_ptr<Player> _player_nato;
    std::shared_ptr<Player> _player_soviet;
};

#pragma mark Game
        
void Game::add_nato_player(const std::string &name)
{
}

void Game::add_soviet_player(const std::string &name)
{
}

std::string Game::current_time()
{
    return "";
}

int Game::current_turn()
{
    return -1;
}

void Game::display_map()
{
    
}

void Game::display_weather()
{
}

std::shared_ptr<Game> Game::factory(std::vector<std::shared_ptr<MapSetup>> map_data)
{
    auto game = std::make_shared<_Game>();
    game->initialize(map_data);
    return game;
}

std::shared_ptr<Map> Game::map()
{
    return nullptr;
}

void Game::next_turn()
{
}

std::shared_ptr<Player> Game::player_nato()
{
    return nullptr;
}

std::shared_ptr<Player> Game::player_soviet()
{
    return nullptr;
}
