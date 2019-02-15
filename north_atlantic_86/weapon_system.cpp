//
//  weapon_system.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/14/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_system.hpp"

#pragma mark _WeaponSystem

class _WeaponSystem : public WeaponSystem
{
    int _accuracy_rating;
    AffiliationType _affiliation;
    int _average_damage;
    std::string _name;
    int _range;
    bool _surface_skimming;
    WeaponSystemType _type;

public:
    _WeaponSystem(const std::string &name, const WeaponSystemType type, const AffiliationType affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming) :
    _accuracy_rating(accuracy_rating), _affiliation(affiliation), _average_damage(average_damage), _name(name), _surface_skimming(surface_skimming), _type(type)
    {
    }
    
    const int accuracy_rating() override
    {
        return _accuracy_rating;
    }
    
    const AffiliationType affiliation() override
    {
        return _affiliation;
    }
    
    const int average_damage() override
    {
        return _average_damage;
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
    
    const WeaponSystemType type() override
    {
        return _type;
    }
};

#pragma mark WeaponSystem

const int WeaponSystem::accuracy_rating()
{
    return -1;
}

const AffiliationType WeaponSystem::affiliation()
{
    return AffiliationType::UNKNOWN;
}

const int WeaponSystem::average_damage()
{
    return -1;
}

const std::string WeaponSystem::name()
{
    return "";
}

// create a weapon system
std::shared_ptr<WeaponSystem> WeaponSystem::Make(const std::string &name, const WeaponSystemType type, const AffiliationType affiliation, const int range, const int average_damage, const int accuracy_rating, const bool surface_skimming)
{
    return std::make_shared<_WeaponSystem>(name, type, affiliation, range, average_damage, accuracy_rating, surface_skimming);
}

const int WeaponSystem::range()
{
    return -1;
}

const bool WeaponSystem::surface_skimming()
{
    return false;
}

const WeaponSystemType WeaponSystem::type()
{
    return WeaponSystemType::Unknown;
}
