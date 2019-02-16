//
//  weapon_mount_exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "exception.hpp"

class weapon_mount_exception : public na_exception
{
public:
    weapon_mount_exception() : na_exception("generic weapon mount exception") {}
    weapon_mount_exception(const std::string &info) : na_exception(info) {}
};

class salvo_too_large_weapon_mount_exception : public weapon_mount_exception
{
public:
    salvo_too_large_weapon_mount_exception(const std::string &info) : weapon_mount_exception("salvo size '" + info + "' too large") {}
};

class not_enough_rounds_weapon_mount_exception : public weapon_mount_exception
{
public:
    not_enough_rounds_weapon_mount_exception(const std::string &info) : weapon_mount_exception("not enough rounds remaining to fire salvo size: '" + info + "'") {}
};
