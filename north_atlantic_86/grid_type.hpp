//
//  grid_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class grid_type : int
{
    Unknown = -1,
    Landmass,
    Ocean,
    Airbase,
    Port
};
    
class grid_type_utility
{
public:
    static const std::string to_string(grid_type t);
};
