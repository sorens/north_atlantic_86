//
//  unit_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "unit_type.hpp"

const std::string UnitTypeUtility::to_string(UnitType t)
{
    switch (t)
    {
        case UnitType::Unknown:
            return "unknown";
            
        case UnitType::Aircraft:
            return "aircraft";
            
        case UnitType::Ship:
            return "ship";
            
        case UnitType::Airbase:
            return "airbase";
            
        case UnitType::Port:
            return "port";
    }
}
