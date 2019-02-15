//
//  ship_data_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"
#include <string>

class ship_data_exception : public na_exception
{
public:
    ship_data_exception() : na_exception("ship data failure") {}
    ship_data_exception(const std::string &info) : na_exception(info) {}
};

class import_failed_ship_data_exception : public ship_data_exception
{
public:
    import_failed_ship_data_exception() : ship_data_exception("failed to import ship data via json") {}
};

class no_ship_data_ship_data_exception : public ship_data_exception
{
public:
    no_ship_data_ship_data_exception() : ship_data_exception("map of ship data missing via json") {}
};

class duplicate_id_ship_data_exception : public ship_data_exception
{
public:
    duplicate_id_ship_data_exception() : ship_data_exception() {}
    duplicate_id_ship_data_exception(const std::string &info) : ship_data_exception("duplicate unit ID {" + info + "}") {}
};

