//
//  map_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "exception.hpp"

#pragma once

class map_exception : public na_exception
{
public:
    map_exception() : na_exception("map failure") {}
    map_exception(const std::string &info) : na_exception(info) {}
};

class map_out_of_bounds_exception : public map_exception
{
public:
    map_out_of_bounds_exception() : map_exception("coordinates do not exist on map") {}
};
