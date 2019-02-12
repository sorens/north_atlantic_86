//
//  game.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/11/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "map.hpp"
#include "map_setup.hpp"
#include "player.hpp"

class Game
{
public:
    // add the nato player
    virtual void add_nato_player(const std::string &name);
    
    // add the soviet player
    virtual void add_soviet_player(const std::string &name);
    
    // return the current time
    virtual std::string current_time();
    
    // return the current_turn
    virtual int current_turn();
    
    // print out the current map
    virtual void display_map();         // debug-only
    
    // print out the current weather
    virtual void display_weather();     // debug-only
    
    // factory method to create a game
    static std::shared_ptr<Game> factory(std::vector<std::shared_ptr<MapSetup>> map_data);
    
    // return a Map
    virtual std::shared_ptr<Map> map();
    
    // run the next turn
    virtual void next_turn();
    
    // return the nato player
    virtual std::shared_ptr<Player> player_nato();
    
    // return the soviet player
    virtual std::shared_ptr<Player> player_soviet();
};
