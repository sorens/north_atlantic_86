//
//  weapon_system.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/14/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_system.hpp"

#include "debug.hpp"
#include <sstream>

#pragma mark _weapon_system

class _weapon_system : public weapon_system
{
    int _accuracy_rating;
    affiliation_type _affiliation;
    int _average_damage;
    int _lraam_salvo_rate;
    std::string _name;
    int _range;
    int _sam_salvo_rate;
    bool _surface_skimming;
    weapon_system_type _type;

public:
    _weapon_system(const std::string &name, const weapon_system_type type, const affiliation_type affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, const int sam_salvo_rate, const int lraam_salvo_rate) :
    _accuracy_rating(accuracy_rating), _affiliation(affiliation), _average_damage(average_damage), _lraam_salvo_rate(lraam_salvo_rate), _name(name), _range(range), _sam_salvo_rate(sam_salvo_rate), _surface_skimming(surface_skimming), _type(type)
    {
    }
    
    const int accuracy_rating() override
    {
        return _accuracy_rating;
    }
    
    const affiliation_type affiliation() override
    {
        return _affiliation;
    }
    
    const int average_damage() override
    {
        return _average_damage;
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<weapon_system";
        ss << " type: '" << weapon_system_type_utility::to_string(_type) << "'";
        ss << ", affiliation: '" << affiliation_utility::to_string(_affiliation) << "'";
        ss << ", range: '" << _range << "'";
        ss << ", name: '" << _name << "'";
        ss << ", average_damage: '" << _average_damage << "'";
        ss << ", accuracy_damage: '" << _accuracy_rating << "'";
        ss << ", surface_skimming: '" << (_surface_skimming ? "yes" : "no") << "'";
        ss << ", sam_salvo_rate: " << _sam_salvo_rate;
        ss << ", lraam_salvo_rate: " << _lraam_salvo_rate;
        ss << ">";
        
        return ss.str();
    }
        
    const int long_range_aam_salvo_rate() override
    {
        return _lraam_salvo_rate;
    }
    
    const std::string name() override
    {
        return _name;
    }
    
    const int range() override
    {
        return _range;
    }
    
    const bool surface_skimming() override
    {
        return _surface_skimming;
    }
        
    const int sam_salvo_rate() override
    {
        return _sam_salvo_rate;
    }
    
    const weapon_system_type type() override
    {
        return _type;
    }
};

#pragma mark weapon_system

const int weapon_system::accuracy_rating()
{
    runtime_assert_not_reached();
}

const affiliation_type weapon_system::affiliation()
{
    runtime_assert_not_reached();
}

const int weapon_system::average_damage()
{
    runtime_assert_not_reached();
}
        
const std::string weapon_system::description()
{
    runtime_assert_not_reached();
}
        
const int weapon_system::long_range_aam_salvo_rate()
{
    runtime_assert_not_reached();
}

const std::string weapon_system::name()
{
    runtime_assert_not_reached();
}

// create a weapon system
std::shared_ptr<weapon_system> weapon_system::Make(const std::string &name, const weapon_system_type type, const affiliation_type affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, int sam_salvo_rate, int lraam_salvo_rate)
{
    return std::make_shared<_weapon_system>(name, type, affiliation, range, average_damage, accuracy_rating, surface_skimming, sam_salvo_rate, lraam_salvo_rate);
}

const int weapon_system::range()
{
    runtime_assert_not_reached();
}
        
const int weapon_system::sam_salvo_rate()
{
    runtime_assert_not_reached();
}

const bool weapon_system::surface_skimming()
{
    runtime_assert_not_reached();
}

const weapon_system_type weapon_system::type()
{
    runtime_assert_not_reached();
}
