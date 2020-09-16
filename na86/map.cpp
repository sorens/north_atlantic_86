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
#include "map_data.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>

# pragma mark _map

class _map : public map
{
public:
    _map()
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }
    
    std::shared_ptr<grid> at(const int x, const int y) override
    {
        if (x < 1 || x > _dimension || y < 1 || y > _dimension)
            throw map_out_of_bounds_exception::factory(x, y);

        int index = static_cast<int>((_map_grid.size() - (y * _dimension)) + x-1);
        if (index < 0 || index >= _map_grid.size())
            throw map_out_of_bounds_exception::factory(x, y);
            
        return _map_grid[index];
    }
    
    std::string description() override
    {
        std::stringstream ss;
        ss << "<map";
        ss << " size: " << _map_grid.size();
        ss << " grid: ";
        bool first = true;
        for (auto g : _map_grid) {
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
        return _map_grid;
    }
    
    void initialize(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data)
    {
        auto setup = map_data::Make(map_data, naval_station_data);

        for (auto &element : setup->map_grid()) {
            _map_grid.push_back(element);
        }
        
        _dimension = std::pow(_map_grid.size(), 0.5);
    }
    
    bool validate_task_force_coordinates(const int x, const int y) override
    {
        // is the grid ocean or port?
        try {
            auto grid = at(x, y);
            if (grid->type() == grid_type::Ocean || grid->type() == grid_type::Port) {
                return true;
            }
        } catch(map_out_of_bounds_exception &e) {
            // handled a map_out_of_bounds_exception, coordinates are
            // not on the map. fall through and return false
        }
        
        return false;
    }
    
private:
    std::vector<std::shared_ptr<grid>> _map_grid;
    int _dimension = -1;
};

#pragma mark Map
        
std::shared_ptr<grid> map::at(const int x, const int y)
{
    runtime_assert_not_reached();
}

std::string map::description()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<grid>> map::grids()
{
    runtime_assert_not_reached();
}

std::shared_ptr<map> map::Make(const std::string &map_data, std::shared_ptr<naval_station_data> naval_station_data)
{
    auto map = std::make_shared<_map>();
    map->initialize(map_data, naval_station_data);
    return map;
}

bool map::validate_task_force_coordinates(const int x, const int y)
{
    runtime_assert_not_reached();
}
