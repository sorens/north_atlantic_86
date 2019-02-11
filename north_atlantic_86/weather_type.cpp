//
//  weather_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weather_type.hpp"

const std::string WeatherTypeUtility::to_string(WeatherType t)
{
    switch (t)
    {
        case WeatherType::Unknown:
            return "unknown";
            
        case WeatherType::Clear:
            return "clear";
            
        case WeatherType::CloudyPartly:
            return "partly cloudy";
            
        case WeatherType::Cloudy:
            return "cloudy";
            
        case WeatherType::Drizzle:
            return "drizzling";
            
        case WeatherType::RainLight:
            return "light rain";
            
        case WeatherType::RainMedium:
            return "medium rain";
            
        case WeatherType::RainHeavy:
            return "heavy rain";
            
        case WeatherType::Storm1:
            return "storm, level 1";
            
        case WeatherType::Storm2:
            return "storm, level 2";
            
        case WeatherType::Storm3:
            return "storm, level 3";
            
        case WeatherType::Gale:
            return "gale";
            
        case WeatherType::Hurricane:
            return "hurricane";
    }
}
