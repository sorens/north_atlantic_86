//
//  fleet.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "unit.hpp"
#include <vector>

class Fleet
{
public:
    // add a unit to this fleet
    virtual void add_unit(std::shared_ptr<Unit> unit);
    
    // factory method to create a fleet
    static std::shared_ptr<Fleet> factory(const std::string &id, const int x, const int y);
    
    // unique ID for this fleet
    virtual const std::string id();
    
    // maximum speed of the fleet (minimium speed of all units in fleet)
    virtual const int max_speed();
    
    // remove the unit from the fleet
    virtual void remove_unit(const std::string &id);
    
    // a list of units in this fleet
    virtual const std::vector<std::weak_ptr<Unit>> units();
    
    // x-coordinate of this fleet
    virtual const int x();
    
    // y-coordinate of this fleet
    virtual const int y();
};
