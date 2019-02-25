//
//  naval_station_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma mark

#include "naval_station.hpp"
#include "weapon_data.hpp"
#include <memory>

class naval_station_data
{
public:
    // find a naval station by its name (e.g. AMERICA or SCAPA FLOW)
    virtual std::shared_ptr<naval_station> find_naval_station(const std::string &name);
    
    // import JSON data
    static const std::string Import_Data(const std::string &path);

    // return naval_station data
    static std::shared_ptr<naval_station_data> Make(const std::string &json_import, std::shared_ptr<WeaponData> weapon_data);
};
