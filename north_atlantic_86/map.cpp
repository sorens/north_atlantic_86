//
//  map.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "map.hpp"

#include "debug.hpp"
#include "grid.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <time.h>

# pragma mark _Map

class _Map : public Map
{
public:
    _Map()
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }
    
    std::shared_ptr<Grid> at(const int x, const int y) override
    {
        int index = (y * _dimension) + x;
        if (index < 0 || index >= _grid.size())
            throw new MapOutOfBoundsException();
            
        return _grid[index];
    }
    
    std::string description() override
    {
        std::stringstream ss;
        ss << "<Map";
        ss << " size: " << _grid.size();
        ss << " grid: ";
        bool first = true;
        for (auto grid : _grid) {
            if (first)
                first = false;
            else
                ss << ", ";
            
            ss << grid->description();
        }
        
        ss << ">";
        
        return ss.str();
    }
    
    const std::vector<std::shared_ptr<Grid>> grid() override
    {
        return _grid;
    }
    
    void initialize(std::vector<std::shared_ptr<MapSetup>> setup, std::shared_ptr<naval_station_data> naval_station_data)
    {
        for (auto &element : setup) {
            GridType type = GridType(static_cast<int>(element->type()));
            std::shared_ptr<Grid> grid = Grid::Make(element->name(), type, element->x(), element->y(), naval_station_data);
            _grid.push_back(grid);
        }
        
        _dimension = std::pow(_grid.size(), 0.5);
    }
        
    std::vector<std::shared_ptr<Unit>> units(const int x, const int y) override
    {
        int index = (y * (_dimension - 1)) + x;
        if (index < 0 || index >= _grid.size())
            throw new MapOutOfBoundsException();
        
        return _grid[index]->units();
    }
    
private:
    std::vector<std::shared_ptr<Grid>> _grid;
    int _dimension = -1;
};

#pragma mark Map
        
std::shared_ptr<Grid> Map::at(const int x, const int y)
{
    runtime_assert_not_reached();
}

std::string Map::description()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Map> Map::factory(std::vector<std::shared_ptr<MapSetup>> setup, std::shared_ptr<naval_station_data> naval_station_data)
{
    auto map = std::make_shared<_Map>();
    map->initialize(setup, naval_station_data);
    return map;
}

const std::vector<std::shared_ptr<Grid>> Map::grid()
{
    runtime_assert_not_reached();
}

std::vector<std::shared_ptr<Unit>> Map::units(const int x, const int y)
{
    runtime_assert_not_reached();
}
