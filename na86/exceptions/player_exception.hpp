//
//  player_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"

class player_exception : public na_exception
{
public:
    player_exception() : na_exception("player exception") {}
    player_exception(const std::string &info) : na_exception(info) {}
};

class no_task_forces_available_player_exception : public player_exception
{
public:
    no_task_forces_available_player_exception() {}
};
