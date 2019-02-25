//
//  grid.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "grid.hpp"
#include "grid_type.hpp"
#include "debug.hpp"
#include "naval_station.hpp"
#include "unit.hpp"
#include "weather.hpp"
#include <cmath>
#include <sstream>
#include <iostream>

#pragma mark _grid

class _grid : public grid
{
public:
    _grid(const std::string &name, grid_type type, const int x, const int y, std::shared_ptr<naval_station_data> naval_station_data) :
    _type(type), _x(x), _y(y), _weather(weather::random())
    {
        if (_type == grid_type::Ocean) {
            // create a random water temperature to start, weather
            // patterns will adjust it later. it will also change with the seasons
            _water_temp = rand() % 35 + 15;
        }
        
        if (!name.empty()) {
            // look up the city, attach
            runtime_assert(naval_station_data);
            _station = naval_station_data->find_naval_station(name);
        }
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<grid";
        ss << " x: " << _x;
        ss << ", y: " << _y;
        ss << ", type: " << grid_type_utility::to_string(_type);
        if (_station)
            ss << ", name: '" << _station->name() << "'";
        if (_type == grid_type::Ocean)
            ss << ", water_temp: " << _water_temp;
        if (_weather) {
            ss << ", " << _weather->description();
        }
        ss << ">";
        return ss.str();
    }
        
    std::shared_ptr<naval_station> station() override
    {
        return _station;
    }
    
    const grid_type type() override
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

    const std::shared_ptr<weather> grid_weather() override
    {
        return _weather;
    }
    
    const std::vector<std::shared_ptr<unit>> units() override
    {
        return _units;
    }
 
private:
    std::shared_ptr<naval_station> _station;
    int _x;
    int _y;
    grid_type _type;
    std::vector<std::shared_ptr<unit>> _units;
    int _water_temp;
    std::shared_ptr<weather> _weather;
};

#pragma mark grid

const std::string grid::description()
{
    runtime_assert_not_reached();
}

int grid::Distance(std::shared_ptr<grid> grid1, std::shared_ptr<grid> grid2)
{
    int result = 0;
    
    int x1 = grid1->x();
    int y1 = grid1->y();
    int x2 = grid2->x();
    int y2 = grid2->y();
    
    int sums = std::pow(x1-x2, 2) + std::pow(y1-y2, 2);
    float d = std::pow(sums, 0.5);
    result = static_cast<int>(std::ceil(d));
    return result;
}

std::shared_ptr<grid> grid::Make(const std::string &name, grid_type type, const int x, const int y, std::shared_ptr<naval_station_data> naval_station_data)
{
    return std::make_shared<_grid>(name, type, x, y, naval_station_data);
}
        
std::shared_ptr<naval_station> grid::station()
{
    runtime_assert_not_reached();
}
        
const grid_type grid::type()
{
    runtime_assert_not_reached();
}

const int grid::x()
{
    runtime_assert_not_reached();
}

const int grid::y()
{
    runtime_assert_not_reached();
}
        
const int grid::water_temperature()
{
    runtime_assert_not_reached();
}

const std::shared_ptr<weather> grid::grid_weather()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<unit>> grid::units()
{
    runtime_assert_not_reached();
}
