//
//  weapon_mount.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_mount.hpp"
#include "weapon_mount_exception.hpp"

#pragma mark _WeaponMount

class _WeaponMount : public WeaponMount
{
    int _magazine_size;
    int _max_salvo_size;
    int _rounds_remaining;
    std::shared_ptr<WeaponSystem> _weapon_system;
    
public:
    _WeaponMount(std::shared_ptr<WeaponSystem> weapon_system, const int magazine_size, const int max_salvo_size) : _magazine_size(magazine_size), _max_salvo_size(max_salvo_size), _rounds_remaining(_magazine_size), _weapon_system(weapon_system)
    {
    }
    
    void fire(const int salvo) override
    {
        if (salvo > _max_salvo_size)
            throw salvo_too_large_weapon_mount_exception(std::to_string(salvo));
            
        if (salvo > _rounds_remaining)
            throw not_enough_rounds_weapon_mount_exception(std::to_string(salvo));
            
        _rounds_remaining -= salvo;
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<WeaponMount";
        ss << " weapon_system: '" << _weapon_system->description() << "'";
        ss << ", magazine_size: '" << _magazine_size<< "'";
        ss << ", max_salvo_size: '" << _max_salvo_size<< "'";
        ss << ", rounds_remaining: '" << _rounds_remaining<< "'";
        ss << ">";
        
        return ss.str();
    }
    
    const bool empty() override
    {
        return _rounds_remaining == _magazine_size;
    }
    
    const int magazine_size() override
    {
        return _magazine_size;
    }
    
    const int max_salvo_size() override
    {
        return _max_salvo_size;
    }
    
    void reload() override
    {
        _rounds_remaining = _magazine_size;
    }
    
    const int rounds_remaining() override
    {
        return _rounds_remaining;
    }
    
    const std::shared_ptr<WeaponSystem> weapon_system() override
    {
        return _weapon_system;
    }
};

#pragma mark WeaponMount

void WeaponMount::fire(const int salvo)
{
}

const std::string WeaponMount::description()
{
    return "";
}

const bool WeaponMount::empty()
{
    return true;
}

const int WeaponMount::magazine_size()
{
    return 0;
}

std::shared_ptr<WeaponMount> WeaponMount::Make(std::shared_ptr<WeaponSystem> weapon_system, const int magazine_size, const int max_salvo_size)
{
    return std::make_shared<_WeaponMount>(weapon_system, magazine_size, max_salvo_size);
}

const int WeaponMount::max_salvo_size()
{
    return 0;
}

void WeaponMount::reload()
{
}

const int WeaponMount::rounds_remaining()
{
    return 0;
}

const std::shared_ptr<WeaponSystem> WeaponMount::weapon_system()
{
    return nullptr;
}
