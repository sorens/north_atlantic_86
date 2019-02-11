//
//  weather_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class WeatherType : int
{
    Unknown = -1,
    Clear,
    CloudyPartly,
    Cloudy,
    Drizzle,
    RainLight,
    RainMedium,
    RainHeavy,
    Storm1,
    Storm2,
    Storm3,
    Gale,
    Hurricane
};

class WeatherTypeUtility
{
public:
    static const std::string to_string(WeatherType t);
};
