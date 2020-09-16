//
//  mutable_naval_station.cpp
//  na86
//
//  Created by Steve Orens on 9/15/20.
//  Copyright © 2020 STEPHEN ORENS. All rights reserved.
//

#include "mutable_naval_station.hpp"
#include "debug.hpp"

#pragma mark _mutable_naval_station

class _mutable_naval_station : public mutable_naval_station
{
    int _infantry;
    int _supplies;
    std::shared_ptr<naval_station> _immutable;

public:

    _mutable_naval_station(std::shared_ptr<naval_station> station) :
    _mutable_naval_station(station, 0, 0)
    {
    }

    _mutable_naval_station(std::shared_ptr<naval_station> station, const int infantry, const int supplies) :
    _immutable(station),
    _infantry(infantry),
    _supplies(supplies)
    {
    }
    
    std::shared_ptr<naval_station> immutable()
    {
        return _immutable;
    }

    void gain_infantry(const int value)
    {
        _infantry += value;
    }
    
    void lose_infantry(const int value)
    {
        _infantry -= value;
        if (_infantry < 0)
            _infantry = 0;
    }
    
    const int infantry()
    {
        return _infantry;
    }

    void gain_supplies(const int value)
    {
        _supplies += value;
    }
    
    void lose_supplies(const int value)
    {
        _supplies -= value;
        if (_supplies < 0)
            _supplies = 0;
    }
    
    const int supplies()
    {
        return _supplies;
    }
};

#pragma mark mutable_naval_station

std::shared_ptr<mutable_naval_station> mutable_naval_station::Make(std::shared_ptr<naval_station> station, const int infantry, const int supplies)
{
    return std::make_shared<_mutable_naval_station>(station, infantry, supplies);
}

// immutable naval_station
std::shared_ptr<naval_station> mutable_naval_station::immutable()
{
    runtime_assert_not_reached();
}

void mutable_naval_station::gain_infantry(const int value)
{
    runtime_assert_not_reached();
}

void mutable_naval_station::lose_infantry(const int value)
{
    runtime_assert_not_reached();
}

const int mutable_naval_station::infantry()
{
    runtime_assert_not_reached();
}

void mutable_naval_station::gain_supplies(const int value)
{
    runtime_assert_not_reached();
}

void mutable_naval_station::lose_supplies(const int value)
{
    runtime_assert_not_reached();
}

const int mutable_naval_station::supplies()
{
    runtime_assert_not_reached();
}
