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

#pragma mark _WeaponSystem

class _WeaponSystem : public WeaponSystem
{
    int _accuracy_rating;
    affilation_type _affiliation;
    int _average_damage;
    int _lraam_salvo_rate;
    std::string _name;
    int _range;
    int _sam_salvo_rate;
    bool _surface_skimming;
    WeaponSystemType _type;

public:
    _WeaponSystem(const std::string &name, const WeaponSystemType type, const affilation_type affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, const int sam_salvo_rate, const int lraam_salvo_rate) :
    _accuracy_rating(accuracy_rating), _affiliation(affiliation), _average_damage(average_damage), _lraam_salvo_rate(lraam_salvo_rate), _name(name), _range(range), _sam_salvo_rate(sam_salvo_rate), _surface_skimming(surface_skimming), _type(type)
    {
    }
    
    const int accuracy_rating() override
    {
        return _accuracy_rating;
    }
    
    const affilation_type affiliation() override
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
        ss << "<WeaponSystem";
        ss << " type: '" << WeaponSystemTypeUtility::to_string(_type) << "'";
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
    
    const WeaponSystemType type() override
    {
        return _type;
    }
};

#pragma mark WeaponSystem

const int WeaponSystem::accuracy_rating()
{
    runtime_assert_not_reached();
}

const affilation_type WeaponSystem::affiliation()
{
    runtime_assert_not_reached();
}

const int WeaponSystem::average_damage()
{
    runtime_assert_not_reached();
}
        
const std::string WeaponSystem::description()
{
    runtime_assert_not_reached();
}
        
const int WeaponSystem::long_range_aam_salvo_rate()
{
    runtime_assert_not_reached();
}

const std::string WeaponSystem::name()
{
    runtime_assert_not_reached();
}

// create a weapon system
std::shared_ptr<WeaponSystem> WeaponSystem::Make(const std::string &name, const WeaponSystemType type, const affilation_type affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming, int sam_salvo_rate, int lraam_salvo_rate)
{
    return std::make_shared<_WeaponSystem>(name, type, affiliation, range, average_damage, accuracy_rating, surface_skimming, sam_salvo_rate, lraam_salvo_rate);
}

const int WeaponSystem::range()
{
    runtime_assert_not_reached();
}
        
const int WeaponSystem::sam_salvo_rate()
{
    runtime_assert_not_reached();
}

const bool WeaponSystem::surface_skimming()
{
    runtime_assert_not_reached();
}

const WeaponSystemType WeaponSystem::type()
{
    runtime_assert_not_reached();
}
