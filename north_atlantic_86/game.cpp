//
//  game.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/11/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "game.hpp"

#include <cmath>
#include <iostream>     // TODO inject
#include "aircraft_data.hpp"
#include "affiliation_type.hpp"
#include "debug.hpp"
#include "log.hpp"
#include "mutable_unit.hpp"
//#include "naval_station.hpp"
#include "naval_station_data.hpp"
#include "ship_data.hpp"
#include "weapon_data.hpp"
#include "weapon_mount.hpp"
#include "weapon_mount_exception.hpp"

#pragma mark _game

// NATO gets 11 active TFs maximum
static const std::vector<std::string> NATO_POSSIBLE_TASK_FORCES     = {"11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"};
// SOVIET gets 9 active TFs maximum
static const std::vector<std::string> SOVIET_POSSIBLE_TASK_FORCES   = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

class _game : public game
{
public:
    _game()
    {
    }
    
    std::shared_ptr<::aircraft> aircraft(const std::string &designation) override
    {
        runtime_assert(_aircraft_data);
        return _aircraft_data->find_aircraft(designation);
    }
    
    void add_nato_player(const std::string &name) override
    {
        _player_nato = Player::Make(affilation_type::NATO, name, NATO_POSSIBLE_TASK_FORCES);
    }
    
    void add_soviet_player(const std::string &name) override
    {
        _player_soviet = Player::Make(affilation_type::SOVIET, name, SOVIET_POSSIBLE_TASK_FORCES);
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
    
    std::shared_ptr<naval_station> find_naval_station(const std::string &name) override
    {
        runtime_assert(_naval_station_data);
        return _naval_station_data->find_naval_station(name);
    }
    
    void initialize(const std::string &map_data,
                        const std::string &ships_json_data,
                        const std::string &weapons_json_data,
                        const std::string &aircraft_json_data,
                        const std::string &naval_station_json_data) {
        _ship_data = ShipData::factory(ships_json_data);
        _weapon_data = WeaponData::Make(weapons_json_data);
        _aircraft_data = aircraft_data::Make(aircraft_json_data, _weapon_data);
        _naval_station_data = naval_station_data::Make(naval_station_json_data, _weapon_data);
        _map = Map::Make(map_data, _naval_station_data);
    }
    
    std::shared_ptr<Map> map() override
    {
        return _map;
    }
        
    void next_turn() override
    {
        // create a task force
        auto combat_tf = _player_nato->create_task_force(TaskForceMissionType::COMBAT, 10, 10);
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
    std::shared_ptr<aircraft_data> _aircraft_data;
    std::shared_ptr<Map> _map;
    int _current_turn;
    std::shared_ptr<naval_station_data> _naval_station_data;
    std::shared_ptr<Player> _player_nato;
    std::shared_ptr<Player> _player_soviet;
    std::shared_ptr<ShipData> _ship_data;
    std::shared_ptr<WeaponData> _weapon_data;
};

#pragma mark game

std::shared_ptr<aircraft> game::aircraft(const std::string &designation)
{
    runtime_assert_not_reached();
}
        
void game::add_nato_player(const std::string &name)
{
    runtime_assert_not_reached();
}

void game::add_soviet_player(const std::string &name)
{
    runtime_assert_not_reached();
}

std::string game::current_time()
{
    runtime_assert_not_reached();
}

int game::current_turn()
{
    runtime_assert_not_reached();
}

void game::display_map()
{
    runtime_assert_not_reached();
}

void game::display_weather()
{
    runtime_assert_not_reached();
}

std::shared_ptr<naval_station> game::find_naval_station(const std::string &name)
{
    runtime_assert_not_reached();
}

std::shared_ptr<game> game::Make(const std::string &map_data,
                                 const std::string &ships_json_data,
                                 const std::string &weapons_json_data,
                                 const std::string &aircraft_json_data,
                                 const std::string &naval_station_json_data)
{
    auto game = std::make_shared<_game>();
    game->initialize(map_data, ships_json_data, weapons_json_data, aircraft_json_data, naval_station_json_data);
    return game;
}

std::shared_ptr<Map> game::map()
{
    runtime_assert_not_reached();
}
        
void game::next_turn()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Player> game::player_nato()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Player> game::player_soviet()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Unit> game::unit(const std::string &id)
{
    runtime_assert_not_reached();
}

std::shared_ptr<WeaponSystem> game::weapon_system(const std::string &id)
{
    runtime_assert_not_reached();
}
