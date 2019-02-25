//
//  weather_type.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weather_type.hpp"

const std::string weather_type_utility::to_string(weather_type t)
{
    switch (t) {
        case weather_type::Unknown:
            return "unknown";
            
        case weather_type::Clear:
            return "clear";
            
        case weather_type::CloudyPartly:
            return "partly cloudy";
            
        case weather_type::Cloudy:
            return "cloudy";
            
        case weather_type::Drizzle:
            return "drizzling";
            
        case weather_type::RainLight:
            return "light rain";
            
        case weather_type::RainMedium:
            return "medium rain";
            
        case weather_type::RainHeavy:
            return "heavy rain";
            
        case weather_type::Storm1:
            return "storm, level 1";
            
        case weather_type::Storm2:
            return "storm, level 2";
            
        case weather_type::Storm3:
            return "storm, level 3";
            
        case weather_type::Gale:
            return "gale";
            
        case weather_type::Hurricane:
            return "hurricane";
    }
}
