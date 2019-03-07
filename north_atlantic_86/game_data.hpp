//
//  game_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/27/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include "aircraft_data.hpp"
#include "map_data.hpp"
#include "naval_station_data.hpp"
#include "ship_data.hpp"
#include "scenario_data.hpp"
#include "weapon_data.hpp"

class game_data
{
public:
    virtual std::shared_ptr<aircraft_data> aircraft();
    virtual std::shared_ptr<map_data> map();
    virtual std::shared_ptr<naval_station_data> stations();
    virtual std::shared_ptr<scenario_data> scenario();
    virtual std::shared_ptr<ship_data> ships();
    virtual std::shared_ptr<weapon_data> weapons();
    
    static std::shared_ptr<game_data> Make(const std::string &aircraft_data,
                                           const std::string &map_data,
                                           const std::string &naval_station_data,
                                           const std::string &scenario_data,
                                           const std::string &ship_data,
                                           const std::string &weapon_data);
};
