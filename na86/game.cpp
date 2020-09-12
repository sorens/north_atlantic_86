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
#include "game_data.hpp"
#include "log.hpp"
#include "mutable_unit.hpp"
//#include "naval_station.hpp"
#include "naval_station_data.hpp"
#include "scenario_data.hpp"
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
        runtime_assert(_game_data);
        runtime_assert(_game_data->aircraft());
        return _game_data->aircraft()->find_aircraft(designation);
    }
    
    void add_nato_player(const std::string &name) override
    {
        _player_nato = player::Make(affiliation_type::NATO, name, NATO_POSSIBLE_TASK_FORCES);
        
        // loop over scenario tasks forces, add them to our player
        for (auto tf : _game_data->scenario()->nato_task_forces()) {
            _player_nato->add_task_force(tf);
        }
    }
    
    void add_soviet_player(const std::string &name) override
    {
        _player_soviet = player::Make(affiliation_type::SOVIET, name, SOVIET_POSSIBLE_TASK_FORCES);
        
        // loop over scenario tasks forces, add them to our player
        for (auto tf : _game_data->scenario()->soviet_task_forces()) {
            _player_soviet->add_task_force(tf);
        }
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
        
        auto grid = _game_map->grids();
        auto size = grid.size();
        int side = std::pow(size, 0.5);
        int i = 0;
        for (auto g : grid) {
            auto weather = g->grid_weather();
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
    
    std::shared_ptr<naval_station> find_naval_station(const std::string &id) override
    {
        runtime_assert(_game_data);
        runtime_assert(_game_data->stations());
        return _game_data->stations()->find_naval_station(id);
    }
    
    std::shared_ptr<map> game_map() override
    {
        return _game_map;
    }
    
    void initialize(const std::string &map_data,
                        const std::string &ships_json_data,
                        const std::string &weapons_json_data,
                        const std::string &aircraft_json_data,
                        const std::string &naval_station_json_data,
                        const std::string &scenario_data) {
        _game_data = game_data::Make(aircraft_json_data,
                                     map_data,
                                     naval_station_json_data,
                                     scenario_data,
                                     ships_json_data,
                                     weapons_json_data);
        _game_map = map::Make(map_data, _game_data->stations());
    }
    
    std::vector<std::shared_ptr<task_force>> task_forces_at_coordinates(const int x, const int y) override
    {
        std::vector<std::shared_ptr<task_force>> tfs;
        
        for (auto tf : player_nato()->task_forces()) {
            if (tf->x() == x && tf->y() == y) {
                tfs.push_back(tf);
            }
        }
        
        for (auto tf : player_soviet()->task_forces()) {
            if (tf->x() == x && tf->y() == y) {
                tfs.push_back(tf);
            }
        }
        
        return tfs;
    }
    
    void next_turn() override
    {
        // create a task force
        auto combat_tf = _player_nato->create_task_force(task_force_mission_type::COMBAT, 10, 10);
        combat_tf->add_unit(ship_unit("CG-47"));     // Ticonderoga
        combat_tf->add_unit(ship_unit("CVN-68"));    // Nimitz
    }
    
    std::shared_ptr<player> player_nato() override
    {
        return _player_nato;
    }

    std::shared_ptr<player> player_soviet() override
    {
        return _player_soviet;
    }
        
    std::shared_ptr<scenario_data> scenario() override
    {
        runtime_assert(_game_data);
        runtime_assert(_game_data->scenario());
        return _game_data->scenario();
    }
    
    std::shared_ptr<unit> ship_unit(const std::string &id) override
    {
        runtime_assert(_game_data);
        runtime_assert(_game_data->ships());
        return _game_data->ships()->find_unit(id);
    }
        
    std::shared_ptr<weapon_system> find_weapon_system(const std::string &id) override
    {
        runtime_assert(_game_data);
        runtime_assert(_game_data->weapons());
        return _game_data->weapons()->find_weapon_system(id);
    }

    void move_task_force(std::shared_ptr<task_force> &task_force, const int x, const int y) override
    {
        if (task_force == nullptr)
            return;
        
        task_force->move(x, y);
    }

private:
    std::shared_ptr<game_data> _game_data;
    std::shared_ptr<map> _game_map;
    int _current_turn;
    std::shared_ptr<player> _player_nato;
    std::shared_ptr<player> _player_soviet;
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

std::shared_ptr<naval_station> game::find_naval_station(const std::string &id)
{
    runtime_assert_not_reached();
}

std::shared_ptr<map> game::game_map()
{
    runtime_assert_not_reached();
}

std::shared_ptr<game> game::Make(const std::string &map_data,
                                 const std::string &ships_json_data,
                                 const std::string &weapons_json_data,
                                 const std::string &aircraft_json_data,
                                 const std::string &naval_station_json_data,
                                 const std::string &scenario_data)
{
    auto game = std::make_shared<_game>();
    game->initialize(map_data, ships_json_data, weapons_json_data, aircraft_json_data, naval_station_json_data, scenario_data);
    return game;
}

void game::move_task_force(std::shared_ptr<task_force> &task_force, const int x, const int y)
{
    runtime_assert_not_reached();
}

void game::next_turn()
{
    runtime_assert_not_reached();
}

std::shared_ptr<player> game::player_nato()
{
    runtime_assert_not_reached();
}

std::shared_ptr<player> game::player_soviet()
{
    runtime_assert_not_reached();
}

std::shared_ptr<scenario_data> game::scenario()
{
    runtime_assert_not_reached();
}

std::shared_ptr<unit> game::ship_unit(const std::string &id)
{
    runtime_assert_not_reached();
}

std::shared_ptr<weapon_system> game::find_weapon_system(const std::string &id)
{
    runtime_assert_not_reached();
}

std::vector<std::shared_ptr<task_force>> game::task_forces_at_coordinates(const int x, const int y)
{
    runtime_assert_not_reached();
}
