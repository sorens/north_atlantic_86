//
//  weapon_mount.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/15/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weapon_mount.hpp"
#include "debug.hpp"
#include "weapon_mount_exception.hpp"

#pragma mark _weapon_mount

class _weapon_mount : public weapon_mount
{
    int _magazine_size;
    int _max_salvo_size;
    int _rounds_remaining;
    std::shared_ptr<weapon_system> _weapon_system;
    
public:
    _weapon_mount(std::shared_ptr<weapon_system> weapon_system, const int magazine_size, const int max_salvo_size) : _magazine_size(magazine_size), _max_salvo_size(max_salvo_size), _rounds_remaining(_magazine_size), _weapon_system(weapon_system)
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
        ss << "<weapon_mount";
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
    
    const std::shared_ptr<weapon_system> system() override
    {
        return _weapon_system;
    }
};

#pragma mark weapon_mount

void weapon_mount::fire(const int salvo)
{
    runtime_assert_not_reached();
}

const std::string weapon_mount::description()
{
    runtime_assert_not_reached();
}

const bool weapon_mount::empty()
{
    runtime_assert_not_reached();
}

const int weapon_mount::magazine_size()
{
    runtime_assert_not_reached();
}

std::shared_ptr<weapon_mount> weapon_mount::Make(std::shared_ptr<weapon_system> weapon_system, const int magazine_size, const int max_salvo_size)
{
    return std::make_shared<_weapon_mount>(weapon_system, magazine_size, max_salvo_size);
}

const int weapon_mount::max_salvo_size()
{
    runtime_assert_not_reached();
}

void weapon_mount::reload()
{
    runtime_assert_not_reached();
}

const int weapon_mount::rounds_remaining()
{
    runtime_assert_not_reached();
}

const std::shared_ptr<weapon_system> weapon_mount::system()
{
    runtime_assert_not_reached();
}
