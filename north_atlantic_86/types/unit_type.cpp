//
//  unit_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "unit_type.hpp"

const std::string unit_type_utility::to_string(unit_type t)
{
    switch (t) {
        case unit_type::Unknown:
            return "unknown";
            
        case unit_type::Aircraft:
            return "aircraft";
            
        case unit_type::Ship:
            return "ship";
            
        case unit_type::Airbase:
            return "airbase";
            
        case unit_type::Port:
            return "port";
    }
}
