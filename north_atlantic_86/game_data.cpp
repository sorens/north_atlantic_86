//
//  game_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/27/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "game_data.hpp"
#include "aircraft_data.hpp"
#include "debug.hpp"
#include "map_data.hpp"
#include "naval_station_data.hpp"
#include "scenario_data.hpp"
#include "ship_data.hpp"
#include "weapon_data.hpp"

class _game_data : public game_data
{

    std::string _aircraft_data;
    std::string _map_data;
    std::string _naval_station_data;
    std::string _scenario_data;
    std::string _ship_data;
    std::string _weapon_data;

    std::shared_ptr<aircraft_data> _aircraft;
    std::shared_ptr<map_data> _map;
    std::shared_ptr<naval_station_data> _naval_stations;
    std::shared_ptr<scenario_data> _scenario;
    std::shared_ptr<ShipData> _ships;
    std::shared_ptr<weapon_data> _weapons;
    
public:
    _game_data(const std::string &aircraft_data,
               const std::string &map_data,
               const std::string &naval_station_data,
               const std::string &scenario_data,
               const std::string &ship_data,
               const std::string &weapon_data) :
    _aircraft_data(aircraft_data),
    _map_data(map_data),
    _naval_station_data(naval_station_data),
    _scenario_data(scenario_data),
    _ship_data(ship_data),
    _weapon_data(weapon_data)
    {
    }
    
    void initialize()
    {
        _ships = ShipData::factory(_ship_data);
        _scenario = scenario_data::Make(_scenario_data, _ships);
        _weapons = weapon_data::Make(_weapon_data);
        _aircraft = aircraft_data::Make(_aircraft_data, _weapons);
        _naval_stations = naval_station_data::Make(_naval_station_data, _weapons, _scenario);
        _map = map_data::Make(_map_data, _naval_stations);
    }

    std::shared_ptr<aircraft_data> aircraft() override
    {
        return _aircraft;
    }

    std::shared_ptr<map_data> map() override
    {
        return _map;
    }

    std::shared_ptr<naval_station_data> stations() override
    {
        return _naval_stations;
    }

    std::shared_ptr<scenario_data> scenario() override
    {
        return _scenario;
    }

    std::shared_ptr<ShipData> ships() override
    {
        return _ships;
    }

    std::shared_ptr<weapon_data> weapons() override
    {
        return _weapons;
    }

};

std::shared_ptr<game_data> game_data::Make(const std::string &aircraft_data,
                                const std::string &map_data,
                                const std::string &naval_station_data,
                                const std::string &scenario_data,
                                const std::string &ship_data,
                                const std::string &weapon_data)
{
    auto game_data = std::make_shared<_game_data>(aircraft_data,
                                        map_data,
                                        naval_station_data,
                                        scenario_data,
                                        ship_data,
                                        weapon_data);
    game_data->initialize();
    return game_data;
}

std::shared_ptr<aircraft_data> game_data::aircraft()
{
    runtime_assert_not_reached();
}

std::shared_ptr<map_data> game_data::map()
{
    runtime_assert_not_reached();
}

std::shared_ptr<naval_station_data> game_data::stations()
{
    runtime_assert_not_reached();
}

std::shared_ptr<scenario_data> game_data::scenario()
{
    runtime_assert_not_reached();
}

std::shared_ptr<ShipData> game_data::ships()
{
    runtime_assert_not_reached();
}

std::shared_ptr<weapon_data> game_data::weapons()
{
    runtime_assert_not_reached();
}

