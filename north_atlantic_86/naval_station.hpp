//
//  naval_station.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "affiliation_type.hpp"
#include "aircraft.hpp"
#include "naval_station_type.hpp"
#include "weapon_system.hpp"
#include "weapon_system_type.hpp"
#include <string>
#include <unordered_map>
#include <vector>

// a base can be an airbase or a port (which includes an airbase)

class naval_station
{
public:
    // affiliation type
    virtual const affilation_type affiliation();

    // aircraft capacity
    virtual const int airbase_capacity();

    // light guns
    virtual const int anti_aircraft_gun();

    // defense factor
    virtual const int defense_factor();

    // electronic warfare strength
    virtual const int ew_strength();

    // helicopters
    virtual const int helicopters();

    // main guns
    virtual const int main_guns();

    // create a naval_station
    static std::shared_ptr<naval_station> Make(const std::string &name, const
                                               affilation_type affiliation,
                                               const naval_station_type type,
                                               const int airbase_capacity,
                                               const int aa,
                                               const int df,
                                               const int ew,
                                               const int helicopters,
                                               const int mg,
                                               const int md,
                                               const int sonar,
                                               std::shared_ptr<weapon_system> ssm,
                                               const int ssm_salvo_rate,
                                               const int ssm_magazine_capacity,
                                               std::shared_ptr<weapon_system> asw,
                                               std::shared_ptr<weapon_system> sam,
                                               std::shared_ptr<weapon_system> ast);

    // missile defense
    virtual const int missible_defense();
    
    // name of naval_station
    virtual const std::string name();

    // sonar strength
    virtual const int sonar_strength();
    
    // naval_station type
    virtual const naval_station_type type();
    
    // weapon system
    virtual std::shared_ptr<weapon_system> find_weapon_system(const weapon_system_type t);
};
