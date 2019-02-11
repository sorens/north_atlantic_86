//
//  map.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "grid.hpp"
#include "map.hpp"
#include <sstream>
#include <iostream>
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
    
    void initialize(std::vector<std::shared_ptr<MapSetup>> setup)
    {
        for (auto &element : setup) {
            GridType type = GridType(static_cast<int>(element->type()));
            std::shared_ptr<Grid> grid = Grid::factory(element->name(), type, element->x(), element->y());
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
    return nullptr;
}

std::string Map::description()
{
    return "";
}

std::shared_ptr<Map> Map::factory(std::vector<std::shared_ptr<MapSetup>> setup)
{
    auto map = std::make_shared<_Map>();
    map->initialize(setup);
    return map;
}

const std::vector<std::shared_ptr<Grid>> Map::grid()
{
    return std::vector<std::shared_ptr<Grid>>(0);
}

std::vector<std::shared_ptr<Unit>> Map::units(const int x, const int y)
{
    return std::vector<std::shared_ptr<Unit>>(0);
}
