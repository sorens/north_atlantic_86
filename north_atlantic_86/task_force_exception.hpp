//
//  task_force_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"

class task_force_exception : public na_exception
{
public:
    task_force_exception() : na_exception("task force failure") {}
    task_force_exception(const std::string &info) : na_exception(info) {}
};

class ship_not_allowed_for_mission_task_force_exception : public task_force_exception
{
public:
    ship_not_allowed_for_mission_task_force_exception(const std::string &info) : task_force_exception(info) {}
};
