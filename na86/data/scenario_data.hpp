//
//  scenario_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/25/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <memory>
#include "player.hpp"
#include "ship_data.hpp"

class scenario_data
{
public:
    // import scenario data
    static const std::string Import_Data(const std::string &path);
    
    // create a scenario container
    static std::shared_ptr<scenario_data> Make(const std::string &json_import, std::shared_ptr<ship_data> ship_data);
    
    // create a player with scenario data
    virtual std::shared_ptr<player> make_player(const affiliation_type affiliation);
  
    // return the nato task forces in this scenario
    virtual std::vector<std::shared_ptr<task_force>> nato_task_forces();
    
    // return the soviet task forces in this scenarip
    virtual std::vector<std::shared_ptr<task_force>> soviet_task_forces();

    // return the infantry for a naval station
    virtual const int station_infantry(const std::string &id);
    
    // return the supplies for a naval station
    virtual const int station_supplies(const std::string &id);
};
