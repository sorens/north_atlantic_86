//
//  mutable_unit.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "unit.hpp"

// MutableUnit provides read and write access to fields
// of a Unit that can be updated during the progress of the game
class MutableUnit : public Unit
{
public:
    // damage
    virtual void apply_damage(const int damage);
    virtual const int damage();

    // return a mutable unit
    static std::shared_ptr<MutableUnit> factory(std::shared_ptr<Unit> unit);
    
    // max speed
    virtual void update_max_speed(const int max_speed);
    virtual const int max_speed();

    // is this unit sunk?
    virtual const bool is_sunk();
    
    // return the immutable unit
    virtual std::shared_ptr<Unit> unit();
};
