//
//  weather.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "weather.hpp"
#include "debug.hpp"
#include <sstream>
#include <time.h>
#include <iostream>

#pragma mark _weather

class _weather : public weather
{
public:
    _weather(const weather_type type, const float radar_modifier,
             const float satellite_modifier, const float sonar_modifier,
             const float speed_modifier, const float visibility_modifier ) :
    _radar_modifier(radar_modifier), _satellite_modifier(satellite_modifier),
    _sonar_modifier(sonar_modifier), _speed_modifier(speed_modifier), _visibility_modifier(visibility_modifier), _type(type)
    {
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<weather";
        ss << " type: '" << weather_type_utility::to_string(_type) << "'";
        ss << ", radar: '" << _radar_modifier << "'";
        ss << ", satellite: '" << _satellite_modifier << "'";
        ss << ", sonar: '" << _sonar_modifier << "'";
        ss << ", speed: '" << _speed_modifier << "'";
        ss << ", visibility: '" << _visibility_modifier << "'";
        ss << ">";
        
        return ss.str();
    }
    
    const float radar_modifier() override
    {
        return _radar_modifier;
    }
    
    const float satellite_modifier() override
    {
        return _satellite_modifier;
    }
    
    const float sonar_modifier() override
    {
        return _sonar_modifier;
    }
    
    const float speed_modifier() override
    {
        return _speed_modifier;
    }
        
    const weather_type type() override
    {
        return _type;
    }
    
    const float visibility_modifier() override
    {
        return _visibility_modifier;
    }
    
private:
    float _radar_modifier;
    float _satellite_modifier;
    float _sonar_modifier;
    float _speed_modifier;
    float _visibility_modifier;
    weather_type _type;
};

#pragma mark Weather

const std::string weather::description()
{
    runtime_assert_not_reached();
}

std::shared_ptr<weather> weather::factory(weather_type type, float radar_modifier,
                                        float satellite_modifier, float sonar_modifier,
                                        float speed_modifier, float visibility_modifier)
{
    return std::make_shared<_weather>(type, radar_modifier, satellite_modifier, sonar_modifier, speed_modifier, visibility_modifier);
}

// how much is radar performance affected
const float weather::radar_modifier()
{
    runtime_assert_not_reached();
}

// create a random weather
std::shared_ptr<weather> weather::random()
{
    float r = ((double) rand() / RAND_MAX);
    int t = static_cast<int>(rand() % static_cast<int>(weather_type::Hurricane));
    return std::make_shared<_weather>(weather_type(t), r, r, r, r, r);
}

// how much is satellite performance affected
const float weather::satellite_modifier()
{
    runtime_assert_not_reached();
}

// how much is sonar performance affected
const float weather::sonar_modifier()
{
    runtime_assert_not_reached();
}

// how much is speed affected
const float weather::speed_modifier()
{
    runtime_assert_not_reached();
}

// return the weather type
const weather_type weather::type()
{
    runtime_assert_not_reached();
}

// how much is visibility affected
const float weather::visibility_modifier()
{
    runtime_assert_not_reached();
}
