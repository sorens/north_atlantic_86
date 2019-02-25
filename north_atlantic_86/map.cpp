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
#include "map_exception.hpp"
#include "map_setup.hpp"
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
    
    std::shared_ptr<grid> at(const int x, const int y) override
    {
        int index = (y * _dimension) + x;
        if (index < 0 || index >= _grid.size())
            throw map_out_of_bounds_exception();
            
        return _grid[index];
    }
    
    std::string description() override
    {
        std::stringstream ss;
        ss << "<Map";
        ss << " size: " << _grid.size();
        ss << " grid: ";
        bool first = true;
        for (auto g : _grid) {
            if (first)
                first = false;
            else
                ss << ", ";
            
            ss << g->description();
        }
        
        ss << ">";
        
        return ss.str();
    }
    
    const std::vector<std::shared_ptr<grid>> grids() override
    {
        return _grid;
    }
    
    void initialize(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data)
    {
        auto setup = MapSetup::factory(map_data);

        for (auto &element : setup) {
            grid_type type = grid_type(static_cast<int>(element->type()));
            std::shared_ptr<grid> grid = grid::Make(element->name(), type, element->x(), element->y(), naval_station_data);
            _grid.push_back(grid);
        }
        
        _dimension = std::pow(_grid.size(), 0.5);
    }
    
    std::vector<std::shared_ptr<Unit>> units(const int x, const int y) override
    {
        int index = (y * (_dimension - 1)) + x;
        if (index < 0 || index >= _grid.size())
            throw map_out_of_bounds_exception();
        
        return _grid[index]->units();
    }
    
private:
    std::vector<std::shared_ptr<grid>> _grid;
    int _dimension = -1;
};

#pragma mark Map
        
std::shared_ptr<grid> Map::at(const int x, const int y)
{
    runtime_assert_not_reached();
}

std::string Map::description()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<grid>> Map::grids()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Map> Map::Make(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data)
{
    auto map = std::make_shared<_Map>();
    map->initialize(map_data, naval_station_data);
    return map;
}

std::vector<std::shared_ptr<Unit>> Map::units(const int x, const int y)
{
    runtime_assert_not_reached();
}
