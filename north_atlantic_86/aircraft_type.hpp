//
//  aircraft_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/21/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class AircraftType : int
{
    Unknown = -1,
    Fighter,
    Attack,
    Transport,
    AWAC,           // Airborn Warning and Control Systems, AIR-EARLY WARNING
    AEW,            // Airborne Electronic Warfare, AIR-EW
    ASW,            // Anti-Submarine Warfare, AIR-ASW
    RECON           // Airborne Reconnaissance Aircraft, AIR-RECON (surface only)
};
    
class AircraftTypeUtility
{
public:
    static const std::string To_String(AircraftType t);
};
