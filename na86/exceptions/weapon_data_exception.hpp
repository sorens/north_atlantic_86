//
//  weapon_data_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"

class weapon_data_exception : public na_exception
{
public:
    weapon_data_exception() : na_exception("generic weapon data exception") {}
    weapon_data_exception(const std::string &info) : na_exception(info) {}
};

class import_failed_weapon_data_exception : public weapon_data_exception
{
public:
    import_failed_weapon_data_exception() : weapon_data_exception("failed to import weapon data via json") {}
    import_failed_weapon_data_exception(const std::string &info) : weapon_data_exception("failed to import weapon data via json: '" + info + "'") {}
};

class no_weapon_data_weapon_data_exception : public weapon_data_exception
{
public:
    no_weapon_data_weapon_data_exception() : weapon_data_exception("map of weapon data missing via json") {}
};
