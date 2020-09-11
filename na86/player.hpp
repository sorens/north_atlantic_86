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
#include "naval_station.hpp"
#include "task_force.hpp"
#include "task_force_mission_type.hpp"
#include "unit.hpp"

class player
{
public:
    // add a task force
    virtual void add_task_force(std::shared_ptr<task_force> tf);
    
    // return the player's affiliation (e.g. NATO, SOVIET)
    virtual const affiliation_type affiliation();
    
    // convert Alliance to a human-readable string
    static const std::string alliance_to_string(const affiliation_type affiliation);
    
    // return a list of ports and airbases
    virtual const std::vector<std::shared_ptr<naval_station>> bases();

    // create a task force, client should catch player_exception and validate that the returned shared_ptr is non-nullptr
    virtual std::shared_ptr<task_force> create_task_force(const task_force_mission_type mission, const int x, const int y);
    
    // disolve a task force
    virtual void dissolve_task_force(std::shared_ptr<task_force> tf);
    
    // return the player's id
    virtual const std::string id();
    
    // factory method to create a player
    static std::shared_ptr<player> Make(const affiliation_type affiliation);
    
    // factory method to create a player
    static std::shared_ptr<player> Make(const affiliation_type affiliation, const std::string &name, std::vector<std::string> task_force_ids);  // TODO bases
    
    // return the player's name
    virtual const std::string name();
    
    // return the number of remaining task forces this player can create
    virtual const int number_remaining_task_forces();
    
    // return the current score
    virtual const int score();
    
    // return a vector of sunken ships
    virtual const std::vector<std::shared_ptr<unit>> sunken_ships();
    
    // return a list of task forces
    virtual const std::vector<std::shared_ptr<task_force>> task_forces();
};
