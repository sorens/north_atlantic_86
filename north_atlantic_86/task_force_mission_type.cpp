//
//  task_force_mission_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "task_force_mission_type.hpp"

#pragma mark TaskForceMissionTypeUtility

int TaskForceMissionTypeUtility::Endurance(TaskForceMissionType t)
{
    switch (t)
    {
        case UNKNOWN:
            return -1;
        case RETURN:
            return 0;
        case COMBAT:
        case BOMBARDMENT:
        case TRANSPORT:
        case EVACUATION:
            return 60;
        case SUBMARINE:
            return 90;
    }
}

// return enum TaskForceMissionType for string
const TaskForceMissionType TaskForceMissionTypeUtility::To_Enum(const std::string &t)
{
    TaskForceMissionType result = UNKNOWN;
    if (t == "COMBAT")
        result = COMBAT;
    else if (t == "BOMBARDMENT")
        result = BOMBARDMENT;
    else if (t == "TRANSPORT")
        result = TRANSPORT;
    else if (t == "EVACUATION")
        result = EVACUATION;
    else if (t == "SUBMARINE")
        result = SUBMARINE;
    else if (t == "RETURN")
        result = RETURN;
    
    return result;
}

// return string for TaskForceMissionType
const std::string TaskForceMissionTypeUtility::To_String(TaskForceMissionType t)
{
    switch (t)
    {
        case UNKNOWN:
            return "UNKNOWN";
        case RETURN:
            return "RETURN";
        case COMBAT:
            return "COMBAT";
        case BOMBARDMENT:
            return "BOMBARDMENT";
        case TRANSPORT:
            return "TRANSPORT";
        case EVACUATION:
            return "EVACUATION";
        case SUBMARINE:
            return "SUBMARINE";
    }
}
