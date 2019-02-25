//
//  aircraft_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/22/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "aircraft.hpp"
#include "weapon_data.hpp"
#include <memory>

class aircraft_data
{
public:
    // return a aircraft_data
    static std::shared_ptr<aircraft_data> Make(const std::string &json_import, std::shared_ptr<WeaponData> weapons_data);
    
    // find an aircraft by it's id (e.g. F14 is a Tomcat fighter)
    virtual std::shared_ptr<Aircraft> find_aircraft(const std::string &id);
    
    // import JSON data
    static const std::string Import_Data(const std::string &path);
};
