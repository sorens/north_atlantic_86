//
//  task_force.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "task_force_mission_type.hpp"
#include "unit.hpp"
#include <vector>

class TaskForce
{
public:
    // add a unit to this task force
    virtual void add_unit(std::shared_ptr<Unit> unit);
    
    // return a human-readable string that describes a task force
    virtual const std::string description();
    
    // unique ID for this task force
    virtual const std::string id();
    
    // create a task force
    static std::shared_ptr<TaskForce> Make(const std::string &id, const task_force_mission_type mission, const int x, const int y);
    
    // maximum speed of the task force (minimium speed of all units in task force)
    virtual const int max_speed();
    
    // mission type for this task force
    virtual const task_force_mission_type mission();
    
    // remove the unit from the task force
    virtual void remove_unit(const std::string &id);
    
    // set the mission type for this task force
    virtual void set_mission_type(const task_force_mission_type mission);
    
    // a list of units in this task force
    virtual const std::vector<std::weak_ptr<Unit>> units();
    
    // x-coordinate of this task force
    virtual const int x();
    
    // y-coordinate of this task force
    virtual const int y();
};
