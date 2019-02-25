//
//  task_force_mission_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "task_force_mission_type.hpp"

#pragma mark TaskForceMissionTypeUtility

int task_force_mission_type_utility::endurance(task_force_mission_type t)
{
    switch (t)
    {
        case task_force_mission_type::UNKNOWN:
            return -1;
        case task_force_mission_type::RETURN:
            return 0;
        case task_force_mission_type::COMBAT:
        case task_force_mission_type::BOMBARDMENT:
        case task_force_mission_type::TRANSPORT:
        case task_force_mission_type::EVACUATION:
            return 60;
        case task_force_mission_type::SUBMARINE:
            return 90;
    }
}

// return enum task_force_mission_type for string
const task_force_mission_type task_force_mission_type_utility::to_enum(const std::string &t)
{
    task_force_mission_type result = task_force_mission_type::UNKNOWN;
    if (t == "COMBAT")
        result = task_force_mission_type::COMBAT;
    else if (t == "BOMBARDMENT")
        result = task_force_mission_type::BOMBARDMENT;
    else if (t == "TRANSPORT")
        result = task_force_mission_type::TRANSPORT;
    else if (t == "EVACUATION")
        result = task_force_mission_type::EVACUATION;
    else if (t == "SUBMARINE")
        result = task_force_mission_type::SUBMARINE;
    else if (t == "RETURN")
        result = task_force_mission_type::RETURN;
    
    return result;
}

// return string for task_force_mission_type
const std::string task_force_mission_type_utility::to_string(task_force_mission_type t)
{
    switch (t) {
        case task_force_mission_type::UNKNOWN:
            return "UNKNOWN";
        case task_force_mission_type::RETURN:
            return "RETURN";
        case task_force_mission_type::COMBAT:
            return "COMBAT";
        case task_force_mission_type::BOMBARDMENT:
            return "BOMBARDMENT";
        case task_force_mission_type::TRANSPORT:
            return "TRANSPORT";
        case task_force_mission_type::EVACUATION:
            return "EVACUATION";
        case task_force_mission_type::SUBMARINE:
            return "SUBMARINE";
    }
}
