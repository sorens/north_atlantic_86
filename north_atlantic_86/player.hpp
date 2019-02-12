//
//  player.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <vector>
#include "fleet.hpp"

enum class Alliance : int
{
    Unknown = -1,
    NATO,
    SOVIET
};
    
class Player
{
public:
    // return the player's alliance (e.g. NATO, SOVIET)
    virtual const Alliance alliance();
    
    // convert Alliance to a human-readable string
    static const std::string alliance_to_string(const Alliance alliance);
    
    // return a list of ports and airbases
    // const std::vector<std::shared_ptr<Base>> bases();
    
    // factory method to create a player
    static std::shared_ptr<Player> factory(const Alliance alliance, const std::string &name);

    // return a list of fleets
    virtual const std::vector<std::shared_ptr<Fleet>> fleets();
    
    // return the player's id
    virtual const std::string id();
    
    // return the player's name
    virtual const std::string name();
    
    // return the current score
    virtual const int score();
    
    // return a vector of sunken ships
    virtual const std::vector<std::shared_ptr<Unit>> sunken_ships();
};
