//
//  mutable_naval_station.hpp
//  na86
//
//  Created by Steve Orens on 9/15/20.
//  Copyright © 2020 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "naval_station.hpp"

class mutable_naval_station : public naval_station
{
public:
    // factory
    static std::shared_ptr<mutable_naval_station> Make(std::shared_ptr<naval_station> station, const int infantry, const int supplies);
    
    // immutable naval_station
    virtual std::shared_ptr<naval_station> immutable();
    
    // infantry
    virtual void gain_infantry(const int value);
    virtual void lose_infantry(const int value);
    virtual const int infantry();
    
    // supplies
    virtual void gain_supplies(const int value);
    virtual void lose_supplies(const int value);
    virtual const int supplies();
    
    // pipeline
    
    // aircraft
};

