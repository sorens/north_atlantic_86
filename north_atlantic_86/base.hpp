//
//  base.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "base_type.hpp"

// a base can be an airbase or a port (which includes an airbase)

class Base
{
public:
    virtual const std::string name();
    virtual const int airbase_capacity();
    virtual const BaseType type();
    virtual bool airfields_suppressed();
};
