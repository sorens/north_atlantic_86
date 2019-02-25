//
//  task_force_mission_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class task_force_mission_type : int
{
    UNKNOWN = 0,
    COMBAT,
    BOMBARDMENT,
    TRANSPORT,
    EVACUATION,
    SUBMARINE,
    RETURN
};

class task_force_mission_type_utility
{
public:
    // mission indurance by type
    static int endurance(task_force_mission_type t);
    
    // return enum TaskForceMissionType for string
    static const task_force_mission_type to_enum(const std::string &t);
    
    // return string for TaskForceMissionType
    static const std::string to_string(task_force_mission_type t);
};
