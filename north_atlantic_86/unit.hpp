//
//  unit.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include "affiliation_type.hpp"
#include "unit_type.hpp"

class unit
{
public:
    // value for unit anti-aircraft gun
    virtual const int anti_aircraft_gun();

    // value for cargo capacity
    virtual const int cargo_capacity();

    // value for defense factor
    virtual const int defense_factor();

    // return a human-readable string that describes a unit
    virtual const std::string description();
    
    // return the unique ID of this unit
    virtual const std::string id();
    
    // factory method to create a unit
    static std::shared_ptr<unit> Make(const std::string &id, const std::string &name, const unit_type type, const std::string &unit_class, const std::string &prefix, const int class_id, const int main_gun, const int aa_gun, const int missile_defense, const int max_speed, const int cargo_capacity, const int defense_factor, const affilation_type affiliation);
    
    // value for unit main gun
    virtual const int main_gun();

    // return the unit maximum speed
    virtual const int max_speed();
    
    // value for missile defense
    virtual const int missile_defense();
    
    // value for the ship prefix (e.g. cvn)
    virtual const std::string prefix();
    
    // return the name of this unit
    virtual const std::string name();
    
    // return the UnitType
    virtual const unit_type type();
    
    // return the unit classification (e.g. CVN)
    virtual const std::string unit_class();
};
