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

class MapOutOfBoundsException : public std::exception
{
public:
    virtual const char * what() noexcept
    {
        return "coordinates do not exist on map";
    }
};


class Map
{
public:
    // return a Grid for particular coordinates
    virtual std::shared_ptr<Grid> at(const int x, const int y);
    
    // returns a human-readable string to describe the map
    virtual std::string description();
    
    // return a vector of all the grid in map-order
    virtual const std::vector<std::shared_ptr<Grid>> grid();
    
    // create a map
    static std::shared_ptr<Map> Make(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data);
    
    // return a list of Units for particular coordinates
    virtual std::vector<std::shared_ptr<Unit>> units(const int x, const int y);
};
