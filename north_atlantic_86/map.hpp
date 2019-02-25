//
//  map.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <vector>
#include "grid.hpp"
#include "naval_station_data.hpp"

class Map
{
public:
    // return a Grid for particular coordinates
    virtual std::shared_ptr<grid> at(const int x, const int y);
    
    // returns a human-readable string to describe the map
    virtual std::string description();
    
    // return a vector of all the grid in map-order
    virtual const std::vector<std::shared_ptr<grid>> grids();
    
    // create a map
    static std::shared_ptr<Map> Make(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data);
    
    // return a list of Units for particular coordinates
    virtual std::vector<std::shared_ptr<Unit>> units(const int x, const int y);
};
