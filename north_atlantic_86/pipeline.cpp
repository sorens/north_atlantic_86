//
//  pipeline.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/26/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "pipeline.hpp"
#include "debug.hpp"

class _pipeline : public pipeline
{
    std::unordered_map<std::string, pipeline_unit> _pipeline_units;
    
public:
    
    _pipeline()
    {
    }
    
    void add_pipeline_unit(const std::string &designation, const int turns_until_arrival) override
    {
        pipeline_unit pu(designation, turns_until_arrival);
        _pipeline_units[designation] = pu;
    }
    
    void remove_pipeline_unit(const std::string &designation) override
    {
        if (designation.empty())
            return;
        
        auto pu = _pipeline_units.find(designation);
        if (pu != _pipeline_units.end())
            _pipeline_units.erase(pu);
    }

    const std::unordered_map<std::string, pipeline_unit> units_in_pipeline() override
    {
        return _pipeline_units;
    }
};

void pipeline::add_pipeline_unit(const std::string &designation, const int turns_until_arrival)
{
    runtime_assert_not_reached();
}

std::shared_ptr<pipeline> pipeline::Make()
{
    return std::make_shared<_pipeline>();
}

void pipeline::remove_pipeline_unit(const std::string &designation)
{
    runtime_assert_not_reached();
}

const std::unordered_map<std::string, pipeline_unit> pipeline::units_in_pipeline()
{
    runtime_assert_not_reached();
}
