//
//  weather.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "weather_type.hpp"

class weather
{
public:
    // describe a weather
    virtual const std::string description();
    
    // factory method to create weather
    static std::shared_ptr<weather> factory(weather_type type, float radar_modifier,
                                            float satellite_modifier, float sonar_modifier,
                                            float speed_modifier, float visibility_modifier);
    
    // how much is radar performance affected
    virtual const float radar_modifier();
    
    // create a random weather
    static std::shared_ptr<weather> random();
    
    // how much is satellite performance affected
    virtual const float satellite_modifier();
    
    // how much is sonar performance affected
    virtual const float sonar_modifier();
    
    // how much is speed affected
    virtual const float speed_modifier();

    // return the weather type
    virtual const weather_type type();

    // how much is visibility affected
    virtual const float visibility_modifier();
};
