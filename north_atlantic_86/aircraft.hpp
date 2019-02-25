//
//  aircraft.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/22/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "affiliation_type.hpp"
#include "weapon_system.hpp"
#include <memory>
#include <string>

class Aircraft
{
public:
    // return the aircraft's affiliation (e.g. NATO, SOVIET)
    virtual const affilation_type affiliation();
    
    // accuracy while bombing, if applicable (otherwise 0)
    virtual const int bomber_accuracy();
    
    // aircraft's designation (e.g. F14)
    virtual const std::string designation();
    
    // aircraft's dogfighting rating
    virtual const int dogfighting_rating();
    
    // aircraft's electronic counter measure rating
    virtual const int ecm_rating();
    
    // is this aircraft capable of sortieing from an aircraft carrier
    virtual const bool is_carrier_aircraft();
    
    // aircraft's name
    virtual const std::string name();

    // aircraft's radar capability
    virtual const int radar_capability();
    
    // aircraft's flying range
    virtual const int range();
    
    // aircraft's primary weapon system
    virtual std::shared_ptr<WeaponSystem> weapon_system();

    // combat specifications
    // lrcap => Long Range Combat Air Patrol
    // cap => normal Combat Air Patrol
    // ew => electronic warfare
    // missiles => when aircraft are inside missile range but too close to dogfight
    // dogfight => when aircraft are to close for missiles
    virtual const int lrcap_missile_ew_avg();
    virtual const int lrcap_missile_ew_max();
    virtual const int lrcap_missile_avg();
    virtual const int lrcap_missile_max();
    virtual const int lrcap_dogfight_ew_avg();
    virtual const int lrcap_dogfight_ew_max();
    virtual const int lrcap_dogfight_avg();
    virtual const int lrcap_dogfight_max();
    virtual const int cap_missile_ew_avg();
    virtual const int cap_missile_ew_max();
    virtual const int cap_missile_avg();
    virtual const int cap_missile_max();
    virtual const int cap_dogfight_ew_avg();
    virtual const int cap_dogfight_ew_max();
    virtual const int cap_dogfight_avg();
    virtual const int cap_dogfight_max();
    
    // return a string description of this aircraft
    virtual const std::string description();

    static std::shared_ptr<Aircraft> Make(const std::string &name, const std::string &designation,
        const int range, const std::shared_ptr<WeaponSystem> weapon_system, const bool is_carrier_aircraft, 
        const affilation_type affiliation, const int ecm_rating, const int dogfighting_rating, 
        const int bomber_accuracy, const int radar_capability, const int lrcap_missile_ew_avg, 
        const int lrcap_missile_ew_max, const int lrcap_missile_avg, const int lrcap_missile_max, 
        const int lrcap_dogfight_ew_avg, const int lrcap_dogfight_ew_max, const int lrcap_dogfight_avg, 
        const int lrcap_dogfight_max, const int cap_missile_ew_avg, const int cap_missile_ew_max, 
        const int cap_missile_avg, const int cap_missile_max, const int cap_dogfight_ew_avg, 
        const int cap_dogfight_ew_max, const int cap_dogfight_avg, const int cap_dogfight_max);
};
