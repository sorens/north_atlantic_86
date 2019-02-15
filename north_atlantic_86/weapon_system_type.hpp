//
//  weapon_system_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class WeaponSystemType : int
{
    Unknown,
    SSM,
    SAM,
    ASW,
    AST
};

class WeaponSystemTypeUtility
{
public:
    static const std::string to_string(WeaponSystemType t);
};
