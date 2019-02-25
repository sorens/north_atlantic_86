//
//  mutable_unit.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "debug.hpp"
#include "mutable_unit.hpp"

#pragma mark _mutable_unit
class _mutable_unit : public mutable_unit
{
public:
    _mutable_unit(std::shared_ptr<Unit> unit) :
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

#pragma mark mutable_unit

void mutable_unit::apply_damage(const int damage)
{
}

const int mutable_unit::damage()
{
    return -1;
}

std::shared_ptr<mutable_unit> mutable_unit::Make(std::shared_ptr<Unit> unit)
{
    return std::make_shared<_mutable_unit>(unit);
}

void mutable_unit::update_max_speed(const int max_speed)
{
}

const int mutable_unit::max_speed()
{
    return -1;
}

const bool mutable_unit::is_sunk()
{
    return false;
}

std::shared_ptr<Unit> mutable_unit::unit()
{
    runtime_assert_not_reached();
}
