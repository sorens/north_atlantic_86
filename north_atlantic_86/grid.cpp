//
//  grid.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "grid.hpp"
#include "map_setup.hpp"
#include "unit.hpp"
#include "weather.hpp"
#include <sstream>
#include <iostream>

#pragma mark GridTypeUtility

const std::string GridTypeUtility::to_string(GridType t)
{
    switch (t)
    {
        case GridType::Unknown:
            return "unknown";
        case GridType::Landmass:
            return "landmass";
        case GridType::Ocean:
            return "ocean";
        case GridType::Airbase:
            return "airbase";
        case GridType::Port:
            return "port";
    }
}

#pragma mark _Grid

class _Grid : public Grid
{
public:
    _Grid(const std::string &name, GridType type, const int x, const int y) :
    _name(name), _type(type), _x(x), _y(y), _weather(Weather::random())
    {
        if (_type == GridType::Ocean) {
            // create a random water temperature to start, weather
            // patterns will adjust it later. it will also change with the seasons
            _water_temp = rand() % 35 + 15;
        }
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<Grid";
        ss << " x: " << _x;
        ss << ", y: " << _y;
        ss << ", type: " << GridTypeUtility::to_string(_type);
        if (!_name.empty())
            ss << ", name: '" << _name << "'";
        if (_type == GridType::Ocean)
            ss << ", water_temp: " << _water_temp;
        if (_weather) {
            ss << ", " << _weather->description();
        }
        ss << ">";
        return ss.str();
    }
        
    const std::string name() override
    {
        return _name;
    }
    
    const GridType type() override
    {
        return _type;
    }
        
    const int x() override
    {
        return _x;
    }
    
    const int y() override
    {
        return _y;
    }
        
    const int water_temperature() override
    {
        return _water_temp;
    }

    const std::shared_ptr<Weather> weather() override
    {
        return _weather;
    }
    
    const std::vector<std::shared_ptr<Unit>> units() override
    {
        return _units;
    }
 
private:
    std::string _name;
    int _x;
    int _y;
    GridType _type;
    std::vector<std::shared_ptr<Unit>> _units;
    int _water_temp;
    std::shared_ptr<Weather> _weather;
};

#pragma mark Grid

const std::string Grid::description()
{
    return "";
}

std::shared_ptr<Grid> Grid::factory(const std::string &name, GridType type, const int x, const int y)
{
    return std::make_shared<_Grid>(name, type, x, y);
}
        
const std::string Grid::name()
{
    return "";
}

const GridType Grid::type()
{
    return GridType::Unknown;
}

const int Grid::x()
{
    return -1;
}

const int Grid::y()
{
    return -1;
}
        
const const int Grid::water_temperature()
{
    return -1;
}

const std::shared_ptr<Weather> Grid::weather()
{
    return nullptr;
}

const std::vector<std::shared_ptr<Unit>> Grid::units()
{
    return std::vector<std::shared_ptr<Unit>>(0);
}
