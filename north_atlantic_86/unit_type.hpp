//
//  unit_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class UnitType : int
{
    Unknown,
    Aircraft,
    Ship,
    Airbase,
    Port
};

class UnitTypeUtility
{
public:
    static const std::string to_string(UnitType t);
};


