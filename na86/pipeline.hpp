//
//  pipeline.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/26/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "pipeline_unit.hpp"
#include <memory>
#include <unordered_map>

class pipeline
{
public:

    // add a unit to the pipeline
    virtual void add_pipeline_unit(const std::string &designation, const int turns_until_arrival);
    
    // create a pipeline
    static std::shared_ptr<pipeline> Make();

    // remove a unit from the pipeline
    virtual void remove_pipeline_unit(const std::string &designation);

    // return a map of all the units in the pipeline
    virtual const std::unordered_map<std::string, pipeline_unit> units_in_pipeline();
};
