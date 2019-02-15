//
//  weapon_system_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_system_type.hpp"

const std::string WeaponSystemTypeUtility::to_string(WeaponSystemType t)
{
    switch (t)
    {
        case WeaponSystemType::Unknown:
            return "Unknown";
        case WeaponSystemType::SSM:
            return "SSM";
        case WeaponSystemType::SAM:
            return "SAM";
        case WeaponSystemType::ASW:
            return "ASW";
        case WeaponSystemType::AST:
            return "AST";
    }
}
