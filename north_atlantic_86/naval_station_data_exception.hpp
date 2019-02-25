//
//  naval_station_data_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"
#include <string>

class naval_station_data_exception : public na_exception
{
public:
    naval_station_data_exception() : na_exception("ship data failure") {}
    naval_station_data_exception(const std::string &info) : na_exception(info) {}
};

class import_failed_naval_station_data_exception : public naval_station_data_exception
{
public:
    import_failed_naval_station_data_exception() : naval_station_data_exception("failed to import naval_station data via json") {}
};

class no_naval_station_data_naval_station_data_exception : public naval_station_data_exception
{
public:
    no_naval_station_data_naval_station_data_exception() : naval_station_data_exception("map of naval station data missing via json") {}
};
