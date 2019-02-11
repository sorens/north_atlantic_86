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
#include "unit_type.hpp"

class Unit
{
public:
    // return a human-readable string that describes a unit
    virtual const std::string description();
    
    // factory method to create a unit
    std::shared_ptr<Unit> factory(const std::string &id, const std::string &name, const UnitType type);

    // return the unique ID of this unit
    virtual const std::string id();
    
    // return the unit maximum speed
    virtual const int max_speed();
    
    // return the name of this unit
    virtual const std::string name();
    
    // return the UnitType
    virtual const UnitType type();
};
