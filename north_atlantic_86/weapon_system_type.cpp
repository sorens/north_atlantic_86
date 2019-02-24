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
        case WeaponSystemType::AAM:
            return "AAM";
        case WeaponSystemType::AAM_LONGRANGE:
            return "AAM_LONGRANGE";
        case WeaponSystemType::ASM:
            return "ASM";
    }
}

const WeaponSystemType WeaponSystemTypeUtility::to_enum(const std::string &t)
{
    if ("SSM" == t)
        return WeaponSystemType::SSM;
    else if ("SAM" == t)
        return WeaponSystemType::SAM;
    else if ("ASW" == t)
        return WeaponSystemType::ASW;
    else if ("AST" == t)
        return WeaponSystemType::AST;
    else if ("AAM" == t)
        return WeaponSystemType::AAM;
    else if ("AAM_LONGRANGE" == t)
        return WeaponSystemType::AAM_LONGRANGE;
    else if ("ASM" == t)
        return WeaponSystemType::ASM;
    
    return WeaponSystemType::Unknown;
}
