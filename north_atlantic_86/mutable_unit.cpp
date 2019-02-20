//
//  mutable_unit.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "debug.hpp"
#include "mutable_unit.hpp"

#pragma mark _MutableUnit
class _MutableUnit : public MutableUnit
{
public:
    _MutableUnit(std::shared_ptr<Unit> unit) :
    _unit(unit)
    {
        _damage = 0;
        _max_speed = unit->max_speed();
    }

    void apply_damage(const int damage) override
    {
        _damage += damage;
    }

    const int damage() override
    {
        return _damage;
    }

    void update_max_speed(const int max_speed) override
    {
        _max_speed = max_speed;
    }

    const int max_speed() override
    {
        return _max_speed;
    }

    const bool is_sunk() override
    {
        return _damage >= _unit->defense_factor();
    }
    
    std::shared_ptr<Unit> unit() override
    {
        return _unit;
    }

private:
    int _damage;
    int _max_speed;
    std::shared_ptr<Unit> _unit;
};

#pragma mark MutableUnit

void MutableUnit::apply_damage(const int damage)
{
}

const int MutableUnit::damage()
{
    return -1;
}

std::shared_ptr<MutableUnit> MutableUnit::factory(std::shared_ptr<Unit> unit)
{
    return std::make_shared<_MutableUnit>(unit);
}

void MutableUnit::update_max_speed(const int max_speed)
{
}

const int MutableUnit::max_speed()
{
    return -1;
}

const bool MutableUnit::is_sunk()
{
    return false;
}

std::shared_ptr<Unit> MutableUnit::unit()
{
    runtime_assert_not_reached();
}
