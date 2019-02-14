//
//  map_setup.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <vector>

enum class MapSetupType : int
{
    Unknown = -1,
    Landmass,
    Ocean,
    Airbase,
    Port
};

class MapSetupUtility
{
public:
    static std::string to_string(MapSetupType t);
};

class MapSetup
{
public:
    // description of the map setup data
    virtual const std::string description();
    
    // import a blob of JSON data
    static std::vector<std::shared_ptr<MapSetup>> factory(const std::string json_import);
    
    // name of airbase or port (empty if not an airbase or port)
    virtual const std::string name();
    
    // return map setup type
    virtual const MapSetupType type();
    
    // x-coordinate
    virtual const int x();
    
    // y-coordinate
    virtual const int y();
};
