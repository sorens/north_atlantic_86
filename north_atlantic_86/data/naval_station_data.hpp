//
//  naval_station_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "naval_station.hpp"
#include "scenario_data.hpp"
#include "weapon_data.hpp"
#include <memory>

class naval_station_data
{
public:
    // find a naval station by it's ID (e.g. AMERICA or FAROES-SOVIET)
    virtual std::shared_ptr<naval_station> find_naval_station(const std::string &id);
    
    // import JSON data
    static const std::string Import_Data(const std::string &path);

    // return naval_station data
    static std::shared_ptr<naval_station_data> Make(const std::string &json_import, std::shared_ptr<weapon_data> weapon_data, std::shared_ptr<scenario_data> scenario_data);
};
