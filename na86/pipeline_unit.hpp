//
//  pipeline_unit.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/26/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

class pipeline_unit
{
    std::string _designation;
    int _turns_until_arrival;

public:
    pipeline_unit();
    pipeline_unit(const std::string designation, const int turns_until_arrival);
    
    const std::string designation();
    void set_turns_until_arrival(const int turns_until_arrival);
    const int turns_until_arrival();
};
