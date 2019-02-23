//
//  aircraft_data_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/22/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"

class aircraft_data_exception : public na_exception
{
public:
    aircraft_data_exception() : na_exception("generic aircraft data exception") {}
    aircraft_data_exception(const std::string &info) : na_exception(info) {}
};

class import_failed_aircraft_data_exception : public aircraft_data_exception
{
public:
    import_failed_aircraft_data_exception() : aircraft_data_exception("failed to import aircraft data via json") {}
    import_failed_aircraft_data_exception(const std::string &info) : aircraft_data_exception("failed to import aircraft data via json: '" + info + "'") {}
};

class no_aircraft_data_aircraft_data_exception : public aircraft_data_exception
{
public:
    no_aircraft_data_aircraft_data_exception() : aircraft_data_exception("map of aircraft data missing via json") {}
};
