//
//  weapon_system_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_system_type.hpp"

const std::string weapon_system_type_utility::to_string(weapon_system_type t)
{
    switch (t) {
        case weapon_system_type::Unknown:
            return "Unknown";
        case weapon_system_type::SSM:
            return "SSM";
        case weapon_system_type::SAM:
            return "SAM";
        case weapon_system_type::ASW:
            return "ASW";
        case weapon_system_type::AST:
            return "AST";
        case weapon_system_type::AAM:
            return "AAM";
        case weapon_system_type::AAM_LONGRANGE:
            return "AAM_LONGRANGE";
        case weapon_system_type::ASM:
            return "ASM";
    }
}

const weapon_system_type weapon_system_type_utility::to_enum(const std::string &t)
{
    if ("SSM" == t)
        return weapon_system_type::SSM;
    else if ("SAM" == t)
        return weapon_system_type::SAM;
    else if ("ASW" == t)
        return weapon_system_type::ASW;
    else if ("AST" == t)
        return weapon_system_type::AST;
    else if ("AAM" == t)
        return weapon_system_type::AAM;
    else if ("AAM_LONGRANGE" == t)
        return weapon_system_type::AAM_LONGRANGE;
    else if ("ASM" == t)
        return weapon_system_type::ASM;
    
    return weapon_system_type::Unknown;
}
