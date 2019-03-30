//
//  grid_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "grid_type.hpp"
#include <string>

const std::string grid_type_utility::to_string(grid_type t)
{
    switch (t) {
        case grid_type::Unknown:
            return "unknown";
        case grid_type::Landmass:
            return "landmass";
        case grid_type::Ocean:
            return "ocean";
        case grid_type::Airbase:
            return "airbase";
        case grid_type::Port:
            return "port";
    }
}
