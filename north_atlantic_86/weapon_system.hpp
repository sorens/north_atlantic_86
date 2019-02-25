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

class weapon_system
{
public:
    // return the accuracy rating
    virtual const int accuracy_rating();
    
    // return the affiliation
    virtual const affilation_type affiliation();
    
    // return the average damage per hit
    virtual const int average_damage();
    
    // return a human-readable string that describes a weapon system
    virtual const std::string description();
    
    // long Range AAM salvo rate
    virtual const int long_range_aam_salvo_rate();
    
    // return the name
    virtual const std::string name();
    
    // create a weapon system
    static std::shared_ptr<weapon_system> Make(const std::string &name, const weapon_system_type type, const affilation_type affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, const int sam_salvo_rate, const int lraam_salvo_rate);

    // return the range
    virtual const int range();
    
    // return the SAM salvo rate
    virtual const int sam_salvo_rate();

    // does this weapon skim the surface?
    virtual const bool surface_skimming();
    
    // type of weapon system
    virtual const weapon_system_type type();
};
