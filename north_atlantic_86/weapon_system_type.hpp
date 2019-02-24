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
    SSM,                // surface-to-surface missile (e.g. Tomahawk)
    SAM,                // surface-to-air missile (e.g. Standard)
    ASW,                // anti-submarine warfare (e.g. SUBROC)
    AST,                // anti-ship torpedo (e.g MK46)
    AAM,                // air-to-air missle (e.g. Sidewinder)
    AAM_LONGRANGE,      // long range air-to-air missle (e.g. Phoenix)
    ASM                 // air-to-surface missile (e.g. Walleye)
};

class WeaponSystemTypeUtility
{
public:
    static const std::string to_string(WeaponSystemType t);
    static const WeaponSystemType to_enum(const std::string &t);
};
