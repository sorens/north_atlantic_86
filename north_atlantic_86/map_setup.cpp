//
//  map_setup.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "json11.hpp"
#include "map_setup.hpp"
#include "map_setup_exception.hpp"
#include <cmath>
#include <iostream>
#include <sstream>

#pragma mark MapSetupUtility

std::string MapSetupUtility::to_string(MapSetupType t)
{
    switch (t)
    {
        case MapSetupType::Unknown:
            return "unknown";
        case MapSetupType::Landmass:
            return "landmass";
        case MapSetupType::Ocean:
            return "ocean";
        case MapSetupType::Airbase:
            return "airbase";
        case MapSetupType::Port:
            return "port";
    }
}

#pragma mark _MapSetup

class _MapSetup : public MapSetup
{
public:
    _MapSetup(const MapSetupType type, const int x, const int y, const std::string &name) :
    _name(name), _type(type), _x(x), _y(y)
    {
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<MapSetup";
        ss << " type: " << MapSetupUtility::to_string(_type);
        ss << ", x: " << _x;
        ss << ", y: " << _y;
        if (!_name.empty())
            ss << ", name: '" << _name << "'";
        ss << ">";
        
        return ss.str();
    }

    const std::string name() override
    {
        return _name;
    }
    
    // return map setup type
    const MapSetupType type() override
    {
        return _type;
    }
    
    // x-coordinate
    const int x() override
    {
        return _x;
    }
    
    // y-coordinate
    const int y() override
    {
        return _y;
    }

private:
    std::string _name;
    MapSetupType _type;
    int _x;
    int _y;
};

#pragma mark MapSetup

// description of the map setup data
const std::string MapSetup::description()
{
    return "";
}

std::vector<std::shared_ptr<MapSetup>> MapSetup::factory(const std::string json_import)
{
    if (json_import.empty())
        throw setup_exception();
    
    std::string error;
    auto json = json11::Json::parse(json_import, error);
    if (!json["map"].is_array())
        throw no_map_setup_exception("json 'map' is not an array");
    
    if (!json["names"].is_array())
        throw no_map_setup_exception("json 'names' is not an array");
    
    auto map = json["map"].array_items();     // array of integers
    auto names = json["names"].array_items(); // array of names
    
    if (map.empty())
        throw no_map_setup_exception("json 'map' is empty");
    
    auto map_size = map.size();
    int n = std::pow(map_size, 0.5);
    
    if (n * n != map_size)
        throw map_not_square_setup_exception();

    int x = 0, y = 0;
    int name_index = 0;
    std::vector<std::shared_ptr<MapSetup>> result;

    for (auto &element : map) {
        std::string name;
        MapSetupType type = static_cast<MapSetupType>(element.int_value());
        
        if (type == MapSetupType::Airbase || type == MapSetupType::Port
            ) {
            if (names.empty())
                throw new name_setup_exception();
            
            name = names[name_index++].string_value();
            
            if (name.length() > 32)
                throw new name_too_long_setup_exception();
        }
        
        auto setup = std::make_shared<_MapSetup>(type, x, y, name);
        result.push_back(setup);
        
        x++;
        if (x >= n) {
            x = 0;
            y++;
        }
    }
    
    return result;
}

// name of airbase or port (empty if not an airbase or port)
const std::string MapSetup::name()
{
    return "";
}

// return map setup type
const MapSetupType MapSetup::type()
{
    return MapSetupType::Unknown;
}

// x-coordinate
const int MapSetup::x()
{
    return -1;
}

// y-coordinate
const int MapSetup::y()
{
    return -1;
}
