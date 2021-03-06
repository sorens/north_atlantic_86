//
//  aircraft.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/22/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "aircraft.hpp"
#include "debug.hpp"

#pragma mark _aircraft

class _aircraft : public aircraft
{
public:
    _aircraft(const std::string &name, const std::string &designation,
    const int range, const std::shared_ptr<weapon_system> weapon_system, const bool is_carrier_aircraft,
    const affiliation_type affiliation, const int ecm_rating, const int dogfighting_rating, 
    const int bomber_accuracy, const int radar_capability, const int lrcap_missile_ew_avg, 
    const int lrcap_missile_ew_max, const int lrcap_missile_avg, const int lrcap_missile_max, 
    const int lrcap_dogfight_ew_avg, const int lrcap_dogfight_ew_max, const int lrcap_dogfight_avg, 
    const int lrcap_dogfight_max, const int cap_missile_ew_avg, const int cap_missile_ew_max, 
    const int cap_missile_avg, const int cap_missile_max, const int cap_dogfight_ew_avg, 
    const int cap_dogfight_ew_max, const int cap_dogfight_avg, const int cap_dogfight_max) 
    : _affiliation(affiliation), _bomber_accuracy(bomber_accuracy), _designation(designation),
    _dogfighting_rating(dogfighting_rating), _ecm_rating(ecm_rating), _is_carrier_aircraft(is_carrier_aircraft),
    _name(name), _radar_capability(radar_capability), _range(range), _weapon_system(weapon_system),
    _lrcap_missile_ew_avg (lrcap_missile_ew_avg), _lrcap_missile_ew_max (lrcap_missile_ew_max), 
    _lrcap_missile_avg (lrcap_missile_avg), _lrcap_missile_max (lrcap_missile_max), 
    _lrcap_dogfight_ew_avg (lrcap_dogfight_ew_avg), _lrcap_dogfight_ew_max (lrcap_dogfight_ew_max), 
    _lrcap_dogfight_avg (lrcap_dogfight_avg), _lrcap_dogfight_max (lrcap_dogfight_max), 
    _cap_missile_ew_avg (cap_missile_ew_avg), _cap_missile_ew_max (cap_missile_ew_max), 
    _cap_missile_avg (cap_missile_avg), _cap_missile_max (cap_missile_max), 
    _cap_dogfight_ew_avg (cap_dogfight_ew_avg), _cap_dogfight_ew_max (cap_dogfight_ew_max), 
    _cap_dogfight_avg (cap_dogfight_avg), _cap_dogfight_max (cap_dogfight_max)
    {
    }

    const affiliation_type affiliation() override
    {
        return _affiliation;
    }

    const int bomber_accuracy() override
    {
        return _bomber_accuracy;
    }

    const std::string designation() override
    {
        return _designation;
    }

    const int dogfighting_rating() override
    {
        return _dogfighting_rating;
    }

    const int ecm_rating() override
    {
        return _ecm_rating;
    }

    const bool is_carrier_aircraft() override
    {
        return _is_carrier_aircraft;
    }

    const std::string name() override
    {
        return _name;
    }

    const int radar_capability() override
    {
        return _radar_capability;
    }

    const int range() override
    {
        return _range;
    }

    std::shared_ptr<weapon_system> aaw_weapon_system() override
    {
        return _weapon_system;
    }

    const int lrcap_missile_ew_avg() override
    {
        return _lrcap_missile_ew_avg;
    }

    const int lrcap_missile_ew_max() override
    {
        return _lrcap_missile_ew_max;
    }

    const int lrcap_missile_avg() override
    {
        return _lrcap_missile_avg;
    }

    const int lrcap_missile_max() override
    {
        return _lrcap_missile_max;
    }

    const int lrcap_dogfight_ew_avg() override
    {
        return _lrcap_dogfight_ew_avg;
    }

    const int lrcap_dogfight_ew_max() override
    {
        return _lrcap_dogfight_ew_max;
    }

    const int lrcap_dogfight_avg() override
    {
        return _lrcap_dogfight_avg;
    }

    const int lrcap_dogfight_max() override
    {
        return _lrcap_dogfight_max;
    }

    const int cap_missile_ew_avg() override
    {
        return _cap_missile_ew_avg;
    }

    const int cap_missile_ew_max() override
    {
        return _cap_missile_ew_max;
    }

    const int cap_missile_avg() override
    {
        return _cap_missile_avg;
    }

    const int cap_missile_max() override
    {
        return _cap_missile_max;
    }

    const int cap_dogfight_ew_avg() override
    {
        return _cap_dogfight_ew_avg;
    }

    const int cap_dogfight_ew_max() override
    {
        return _cap_dogfight_ew_max;
    }

    const int cap_dogfight_avg() override
    {
        return _cap_dogfight_avg;
    }

    const int cap_dogfight_max() override
    {
        return _cap_dogfight_max;
    }

    const std::string description() override
    {
        std::stringstream ss;
        
        ss << "<aircraft ";
        ss << "affiliation: " << affiliation_utility::to_string(_affiliation);
        ss << ", bomber_accuracy: " << _bomber_accuracy;
        ss << ", designation: " << _designation;
        ss << ", dogfighting_rating: " << _dogfighting_rating;
        ss << ", ecm_rating: " << _ecm_rating;
        ss << ", is_carrier_aircraft: " << _is_carrier_aircraft;
        ss << ", name: " << _name;
        ss << ", radar_capability: " << _radar_capability;
        ss << ", range: " << _range;
        ss << ", weapon_system: " << _weapon_system->description();
        ss << ", lrcap_missile_ew_avg: " << _lrcap_missile_ew_avg;
        ss << ", lrcap_missile_ew_max: " << _lrcap_missile_ew_max;
        ss << ", lrcap_missile_avg: " << _lrcap_missile_avg;
        ss << ", lrcap_missile_max: " << _lrcap_missile_max;
        ss << ", lrcap_dogfight_ew_avg: " << _lrcap_dogfight_ew_avg;
        ss << ", lrcap_dogfight_ew_max: " << _lrcap_dogfight_ew_max;
        ss << ", lrcap_dogfight_avg: " << _lrcap_dogfight_avg;
        ss << ", lrcap_dogfight_max: " << _lrcap_dogfight_max;
        ss << ", cap_missile_ew_avg: " << _cap_missile_ew_avg;
        ss << ", cap_missile_ew_max: " << _cap_missile_ew_max;
        ss << ", cap_missile_avg: " << _cap_missile_avg;
        ss << ", cap_missile_max: " << _cap_missile_max;
        ss << ", cap_dogfight_ew_avg: " << _cap_dogfight_ew_avg;
        ss << ", cap_dogfight_ew_max: " << _cap_dogfight_ew_max;
        ss << ", cap_dogfight_avg: " << _cap_dogfight_avg;
        ss << ", cap_dogfight_max: " << _cap_dogfight_max;
        ss << ">";
        return ss.str();
    }

private:

    affiliation_type _affiliation;
    int _bomber_accuracy;
    std::string _designation;
    int _dogfighting_rating;
    int _ecm_rating;
    bool _is_carrier_aircraft;
    std::string _name;
    int _radar_capability;
    int _range;
    std::shared_ptr<weapon_system> _weapon_system;

    int _lrcap_missile_ew_avg;
    int _lrcap_missile_ew_max;
    int _lrcap_missile_avg;
    int _lrcap_missile_max;
    int _lrcap_dogfight_ew_avg;
    int _lrcap_dogfight_ew_max;
    int _lrcap_dogfight_avg;
    int _lrcap_dogfight_max;
    int _cap_missile_ew_avg;
    int _cap_missile_ew_max;
    int _cap_missile_avg;
    int _cap_missile_max;
    int _cap_dogfight_ew_avg;
    int _cap_dogfight_ew_max;
    int _cap_dogfight_avg;
    int _cap_dogfight_max;
};

#pragma mark aircraft

const affiliation_type aircraft::affiliation()
{
    runtime_assert_not_reached();
}
    
const int aircraft::bomber_accuracy()
{
    runtime_assert_not_reached();
}
    
const std::string aircraft::designation()
{
    runtime_assert_not_reached();
}
    
const int aircraft::dogfighting_rating()
{
    runtime_assert_not_reached();
}
    
const int aircraft::ecm_rating()
{
    runtime_assert_not_reached();
}
    
const bool aircraft::is_carrier_aircraft()
{
    runtime_assert_not_reached();
}
    
const std::string aircraft::name()
{
    runtime_assert_not_reached();
}
    
const int aircraft::radar_capability()
{
    runtime_assert_not_reached();
}
    
const int aircraft::range()
{
    runtime_assert_not_reached();
}
    
std::shared_ptr<weapon_system> aircraft::aaw_weapon_system()
{
    runtime_assert_not_reached();
}

const int aircraft::lrcap_missile_ew_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_missile_ew_max()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_missile_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_missile_max()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_dogfight_ew_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_dogfight_ew_max()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_dogfight_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::lrcap_dogfight_max()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_missile_ew_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_missile_ew_max()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_missile_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_missile_max()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_dogfight_ew_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_dogfight_ew_max()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_dogfight_avg()
{
    runtime_assert_not_reached();
}
const int aircraft::cap_dogfight_max()
{
    runtime_assert_not_reached();
}
    
const std::string aircraft::description()
{
    runtime_assert_not_reached();
}

std::shared_ptr<aircraft> aircraft::Make(const std::string &name,
                                         const std::string &designation,
                                         const int range,
                                         const std::shared_ptr<weapon_system> weapon_system,
                                         const bool is_carrier_aircraft,
                                         const affiliation_type affiliation,
                                         const int ecm_rating,
                                         const int dogfighting_rating,
                                         const int bomber_accuracy,
                                         const int radar_capability,
                                         const int lrcap_missile_ew_avg,
                                         const int lrcap_missile_ew_max,
                                         const int lrcap_missile_avg,
                                         const int lrcap_missile_max,
                                         const int lrcap_dogfight_ew_avg,
                                         const int lrcap_dogfight_ew_max,
                                         const int lrcap_dogfight_avg,
                                         const int lrcap_dogfight_max,
                                         const int cap_missile_ew_avg,
                                         const int cap_missile_ew_max,
                                         const int cap_missile_avg,
                                         const int cap_missile_max,
                                         const int cap_dogfight_ew_avg,
                                         const int cap_dogfight_ew_max,
                                         const int cap_dogfight_avg,
                                         const int cap_dogfight_max)
{
    return std::make_shared<_aircraft>(name,
                                       designation,
                                       range,
                                       weapon_system,
                                       is_carrier_aircraft,
                                       affiliation,
                                       ecm_rating,
                                       dogfighting_rating,
                                       bomber_accuracy,
                                       radar_capability,
                                       lrcap_missile_ew_avg,
                                       lrcap_missile_ew_max,
                                       lrcap_missile_avg,
                                       lrcap_missile_max,
                                       lrcap_dogfight_ew_avg,
                                       lrcap_dogfight_ew_max,
                                       lrcap_dogfight_avg,
                                       lrcap_dogfight_max,
                                       cap_missile_ew_avg,
                                       cap_missile_ew_max,
                                       cap_missile_avg,
                                       cap_missile_max,
                                       cap_dogfight_ew_avg,
                                       cap_dogfight_ew_max,
                                       cap_dogfight_avg,
                                       cap_dogfight_max);
}
