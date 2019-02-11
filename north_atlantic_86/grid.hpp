//
//  grid.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "unit.hpp"
#include "weather.hpp"
#include <string>
#include <vector>

enum class GridType : int
{
    Unknown = -1,
    Landmass,
    Ocean,
    Airbase,
    Port
};
    
class GridTypeUtility
{
public:
    static const std::string to_string(GridType t);
};

class Grid
{
public:
    // description of a grid
    virtual const std::string description();
    
    // factory to create a grid object
    static std::shared_ptr<Grid> factory(const std::string &name, GridType type, const int x, const int y);
    
    // return the name, if any, of this grid
    virtual const std::string name();
    
    // return the grid type of this grid
    virtual const GridType type();
    
    // return x-coordinate of this grid
    virtual const int x();
    
    // return y-coordinate of this grid
    virtual const int y();
    
    // return the current Weather for this grid
    virtual const std::shared_ptr<Weather> weather();
    
    // return the vector of Units at this grid
    virtual const std::vector<std::shared_ptr<Unit>> units();
};
