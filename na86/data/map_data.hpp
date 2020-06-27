//
//  map_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "grid.hpp"
#include "naval_station_data.hpp"
#include <memory>
#include <vector>

class map_data
{
public:
    // return a vector of the grid for the map_data
    virtual const std::vector<std::shared_ptr<grid>> map_grid();
    
    // import the map_data as a blob of json data
    static const std::string Import_Data(const std::string &path);
    
    // create map_data for map to use
    static std::shared_ptr<map_data> Make(const std::string &json_import, std::shared_ptr<naval_station_data> naval_station_data);
};
