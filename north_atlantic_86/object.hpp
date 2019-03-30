//
//  object.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 3/6/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

class object
{
public:
    // save object as a string in json format
    virtual const std::string save();
    
    // load object from a json representation
    virtual void load(const std::string &data);
};
