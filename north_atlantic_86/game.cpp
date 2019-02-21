//
//  game.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/11/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <cmath>
#include <iostream>     // TODO inject
#include "affiliation_type.hpp"
#include "debug.hpp"
#include "game.hpp"
#include "log.hpp"
#include "mutable_unit.hpp"
#include "ship_data.hpp"
#include "weapon_data.hpp"
#include "weapon_mount.hpp"
#include "weapon_mount_exception.hpp"

#pragma mark _Game

class _Game : public Game
{
public:
    _Game()
    {
    }
    
    void add_nato_player(const std::string &name) override
    {
        _player_nato = Player::factory(AffiliationType::NATO, name);
    }
    
    void add_soviet_player(const std::string &name) override
    {
        _player_soviet = Player::factory(AffiliationType::SOVIET, name);
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
    
    void initialize(std::vector<std::shared_ptr<MapSetup>> map_data, const std::string &ships_json_data, const std::string &weapons_json_data)
    {
        _map = Map::factory(map_data);
        _ship_data = ShipData::factory(ships_json_data);
        _weapon_data = WeaponData::Make(weapons_json_data);
    }
    
    std::shared_ptr<Map> map() override
    {
        return _map;
    }
    
    void next_turn() override
    {
        // create a task force
        auto combat_tf = TaskForce::Make("11", TaskForceMissionType::COMBAT, 10, 10);
        combat_tf->add_unit(unit("CG-47"));     // Ticonderoga
        combat_tf->add_unit(unit("CVN-68"));    // Nimitz
    }
    
    std::shared_ptr<Player> player_nato() override
    {
        return _player_nato;
    }

    std::shared_ptr<Player> player_soviet() override
    {
        return _player_soviet;
    }
    
    std::shared_ptr<Unit> unit(const std::string &id) override
    {
        if (_ship_data) {
            return _ship_data->find_unit(id);
        }
        
        return nullptr;
    }
        
    std::shared_ptr<WeaponSystem> weapon_system(const std::string &id) override
    {
        return _weapon_data->weapon_system(id);
    }

private:
    std::shared_ptr<Map> _map;
    int _current_turn;
    std::shared_ptr<Player> _player_nato;
    std::shared_ptr<Player> _player_soviet;
    std::shared_ptr<ShipData> _ship_data;
    std::shared_ptr<WeaponData> _weapon_data;
};

#pragma mark Game
        
void Game::add_nato_player(const std::string &name)
{
    runtime_assert_not_reached();
}

void Game::add_soviet_player(const std::string &name)
{
    runtime_assert_not_reached();
}

std::string Game::current_time()
{
    runtime_assert_not_reached();
}

int Game::current_turn()
{
    runtime_assert_not_reached();
}

void Game::display_map()
{
    runtime_assert_not_reached();
}

void Game::display_weather()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Game> Game::Make(std::vector<std::shared_ptr<MapSetup>> map_data, const std::string &ships_json_data, const std::string &weapons_json_data)
{
    auto game = std::make_shared<_Game>();
    game->initialize(map_data, ships_json_data, weapons_json_data);
    return game;
}

std::shared_ptr<Map> Game::map()
{
    runtime_assert_not_reached();
}

void Game::next_turn()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Player> Game::player_nato()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Player> Game::player_soviet()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Unit> Game::unit(const std::string &id)
{
    runtime_assert_not_reached();
}

std::shared_ptr<WeaponSystem> Game::weapon_system(const std::string &id)
{
    runtime_assert_not_reached();
}
