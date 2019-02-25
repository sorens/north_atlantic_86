//
//  grid.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "grid.hpp"
#include "debug.hpp"
#include "map_setup.hpp"
#include "naval_station.hpp"
#include "unit.hpp"
#include "weather.hpp"
#include <cmath>
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
    _Grid(const std::string &name, GridType type, const int x, const int y, std::shared_ptr<naval_station_data> naval_station_data) :
    _type(type), _x(x), _y(y), _weather(Weather::random())
    {
        if (_type == GridType::Ocean) {
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
        ss << "<Grid";
        ss << " x: " << _x;
        ss << ", y: " << _y;
        ss << ", type: " << GridTypeUtility::to_string(_type);
        if (_station)
            ss << ", name: '" << _station->name() << "'";
        if (_type == GridType::Ocean)
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
    std::shared_ptr<naval_station> _station;
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
    runtime_assert_not_reached();
}

int Grid::Distance(std::shared_ptr<Grid> grid1, std::shared_ptr<Grid> grid2)
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

std::shared_ptr<Grid> Grid::Make(const std::string &name, GridType type, const int x, const int y, std::shared_ptr<naval_station_data> naval_station_data)
{
    return std::make_shared<_Grid>(name, type, x, y, naval_station_data);
}
        
std::shared_ptr<naval_station> Grid::station()
{
    runtime_assert_not_reached();
}
        
const GridType Grid::type()
{
    runtime_assert_not_reached();
}

const int Grid::x()
{
    runtime_assert_not_reached();
}

const int Grid::y()
{
    runtime_assert_not_reached();
}
        
const int Grid::water_temperature()
{
    runtime_assert_not_reached();
}

const std::shared_ptr<Weather> Grid::weather()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<Unit>> Grid::units()
{
    runtime_assert_not_reached();
}
