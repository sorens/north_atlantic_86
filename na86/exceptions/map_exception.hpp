//
//  map_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "exception.hpp"
#include <stdio.h>
#include <string>

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
    static map_out_of_bounds_exception factory(const int x, const int y) {
        std::stringstream ss;
        ss << "invalid coordinates: " << x << ", " << y;
        return map_out_of_bounds_exception(ss.str());
    }
private:
    map_out_of_bounds_exception(const std::string &info) : map_exception(info) {}
};
