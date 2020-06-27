//
//  pipeline_unit.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/26/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "pipeline_unit.hpp"

#pragma mark pipeline_unit

pipeline_unit::pipeline_unit()
{
}

pipeline_unit::pipeline_unit(const std::string designation, const int turns_until_arrival) :
_designation(designation), _turns_until_arrival(turns_until_arrival)
{
}

const std::string pipeline_unit::designation()
{
    return _designation;
}

void pipeline_unit::set_turns_until_arrival(const int turns_until_arrival)
{
    _turns_until_arrival = turns_until_arrival;
}

const int pipeline_unit::turns_until_arrival()
{
    return _turns_until_arrival;
}
