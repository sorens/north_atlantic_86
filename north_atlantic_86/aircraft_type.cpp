//
//  aircraft_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/21/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "aircraft_type.hpp"

#pragma mark AircraftType

const std::string AircraftTypeUtility::To_String(AircraftType t)
{
    switch (t) {
        case AircraftType::Unknown:
            return "Unknown";
        case AircraftType::Fighter:
            return "Fighter";
        case AircraftType::Attack:
            return "Attack";
        case AircraftType::Transport:
            return "Transport";
        case AircraftType::AWAC:
            return "AWAC";
        case AircraftType::AEW:
            return "AEW";
        case AircraftType::ASW:
            return "ASW";
        case AircraftType::RECON:
            return "RECON";
    }
}
