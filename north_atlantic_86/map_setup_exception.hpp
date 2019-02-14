//
//  map_setup_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/14/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"
#include <string>

class setup_exception : public na_exception
{
public:
    setup_exception() : na_exception("setup failed") {}
    setup_exception(const std::string &id) : na_exception(id) {}
};

class no_map_setup_exception : public setup_exception
{
public:
    no_map_setup_exception() : setup_exception("map missing from json data") {}
    no_map_setup_exception(const std::string &id) : setup_exception(id) {}
};

class map_not_square_setup_exception : public setup_exception
{
public:
    map_not_square_setup_exception() : setup_exception("map data must be N x N in size") {}
};

class name_setup_exception : public setup_exception
{
public:
    name_setup_exception() : setup_exception("name missing from json data") {}
};

class name_too_long_setup_exception : public setup_exception
{
public:
    name_too_long_setup_exception() : setup_exception("name is too long, should 32 characters or less") {}
};

