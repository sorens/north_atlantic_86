//
//  unit_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class unit_type : int
{
    Unknown,
    Aircraft,
    Ship,
    Airbase,
    Port
};

class unit_type_utility
{
public:
    static const std::string to_string(unit_type t);
};


