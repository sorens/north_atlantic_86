//
//  grid.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "grid_type.hpp"
#include "naval_station.hpp"
#include "naval_station_data.hpp"
#include "unit.hpp"
#include "weather.hpp"
#include <string>
#include <vector>

class grid
{
public:
    // add the unit to this grid
    virtual void add_unit(std::shared_ptr<unit> unit);
    
    // clear units
    virtual void clear_units();
    
    // description of a grid
    virtual const std::string description();
    
    // calculate the distance between two grid points
    static int Distance(std::shared_ptr<grid> grid1, std::shared_ptr<grid> grid2);
    
    // return the current Weather for this grid
    virtual const std::shared_ptr<weather> grid_weather();

    // factory to create a grid object
    static std::shared_ptr<grid> Make(const std::string &name, grid_type type, const int x, const int y, std::shared_ptr<naval_station_data> naval_station_data);
    
    // remove the unit from this grid
    virtual void remove_unit(std::shared_ptr<unit> unit);
    
    // return a naval_station at this grid, if one exists
    virtual std::shared_ptr<naval_station> station();
    
    // return the grid type of this grid
    virtual const grid_type type();
    
    // return the vector of Units at this grid
    virtual const std::vector<std::shared_ptr<unit>> units();

    // return x-coordinate of this grid
    virtual const int x();
    
    // return y-coordinate of this grid
    virtual const int y();
    
    // return the water temperature at this location, if applicable
    // if landmass or port/airbase, return -1
    virtual const int water_temperature();
};
