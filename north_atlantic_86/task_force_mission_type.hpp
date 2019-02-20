//
//  task_force_mission_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

typedef enum TaskForceMissionType : int TaskForceMissionType;
enum TaskForceMissionType : int
{
    UNKNOWN = 0,
    COMBAT,
    BOMBARDMENT,
    TRANSPORT,
    EVACUATION,
    SUBMARINE,
    RETURN
};

class TaskForceMissionTypeUtility
{
public:
    // mission indurance by type
    static int Endurance(TaskForceMissionType t);
    
    // return enum TaskForceMissionType for string
    static const TaskForceMissionType To_Enum(const std::string &t);
    
    // return string for TaskForceMissionType
    static const std::string To_String(TaskForceMissionType t);
};
