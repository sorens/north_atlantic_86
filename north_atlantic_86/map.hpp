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
#include "map_setup.hpp"

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
    
    // factory method to create a map
    static std::shared_ptr<Map> factory(std::vector<std::shared_ptr<MapSetup>> setup);
    
    // return a vector of all the grid in map-order
    virtual const std::vector<std::shared_ptr<Grid>> grid();
    
    // return a list of Units for particular coordinates
    virtual std::vector<std::shared_ptr<Unit>> units(const int x, const int y);
};
