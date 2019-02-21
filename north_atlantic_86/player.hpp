//
//  player.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <vector>
#include "affiliation_type.hpp"
#include "task_force.hpp"
#include "unit.hpp"

class Player
{
public:
    // return the player's affiliation (e.g. NATO, SOVIET)
    virtual const AffiliationType affiliation();
    
    // add a task force
    virtual void add_task_force(std::shared_ptr<TaskForce> task_force);
    
    // convert Alliance to a human-readable string
    static const std::string alliance_to_string(const AffiliationType affiliation);
    
    // return a list of ports and airbases
    // const std::vector<std::shared_ptr<Base>> bases();
    
    virtual std::shared_ptr<TaskForce> create_task_force(const TaskForceMissionType mission, const int x, const int y);
    
    // factory method to create a player
    static std::shared_ptr<Player> factory(const AffiliationType affiliation, const std::string &name);

    // return the player's id
    virtual const std::string id();
    
    // return the player's name
    virtual const std::string name();
    
    // return the current score
    virtual const int score();
    
    // return a vector of sunken ships
    virtual const std::vector<std::shared_ptr<Unit>> sunken_ships();
    
    // return a list of task forces
    virtual const std::vector<std::shared_ptr<TaskForce>> task_forces();
};
