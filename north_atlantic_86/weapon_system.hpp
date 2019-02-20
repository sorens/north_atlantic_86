//
//  weapon_system.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/14/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>
#include "weapon_system_type.hpp"
#include "affiliation_type.hpp"

class WeaponSystem
{
public:
    // return the accuracy rating
    virtual const int accuracy_rating();
    
    // return the affiliation
    virtual const AffiliationType affiliation();
    
    // return the average damage per hit
    virtual const int average_damage();
    
    // return a human-readable string that describes a weapon system
    virtual const std::string description();
    
    // return the name
    virtual const std::string name();
    
    // create a weapon system
    static std::shared_ptr<WeaponSystem> Make(const std::string &name, const WeaponSystemType tye, const AffiliationType affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, int sam_salvo_rate);

    // return the range
    virtual const int range();
    
    // return the SAM salvo rate
    virtual const int sam_salvo_rate();

    // does this weapon skim the surface?
    virtual const bool surface_skimming();
    
    // type of weapon system
    virtual const WeaponSystemType type();
};
