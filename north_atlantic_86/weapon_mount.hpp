//
//  weapon_mount.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "weapon_system.hpp"

class weapon_mount
{
public:
    // fire a salvo
    virtual void fire(const int salvo);
        // throws
        // salvo_too_large_weapon_mount_exception,
        // magazine_empty_weapon_mount_exception
    
    // return a human-readable string that describes a weapon mount
    virtual const std::string description();
    
    // is the magazine empty
    virtual const bool empty();

    // total size of the magazine
    virtual const int magazine_size();
    
    // create a weapon mount
    static std::shared_ptr<weapon_mount> Make(std::shared_ptr<WeaponSystem> weapon_system, const int magazine_size, const int max_salvo_size);
    
    // the maximum size of a salvo
    virtual const int max_salvo_size();
    
    // reload the magazine
    virtual void reload();

    // how many rounds remain to be fired
    virtual const int rounds_remaining();
    
    // the weapon system
    virtual const std::shared_ptr<WeaponSystem> weapon_system();
};
