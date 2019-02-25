//
//  aircraft_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/21/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "aircraft_type.hpp"

#pragma mark aircraft_type

const std::string aircraft_type_utility::to_string(aircraft_type t)
{
    switch (t) {
        case aircraft_type::Unknown:
            return "Unknown";
        case aircraft_type::Fighter:
            return "Fighter";
        case aircraft_type::Attack:
            return "Attack";
        case aircraft_type::Transport:
            return "Transport";
        case aircraft_type::AWAC:
            return "AWAC";
        case aircraft_type::AEW:
            return "AEW";
        case aircraft_type::ASW:
            return "ASW";
        case aircraft_type::RECON:
            return "RECON";
    }
}
