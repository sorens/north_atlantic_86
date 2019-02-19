//
//  ship_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "unit.hpp"

class ShipData
{
public:
    // return a ship_data
    static std::shared_ptr<ShipData> factory(const std::string &json_import);
    
    // find a ship by it's id (e.g. CVN-68 is the USS Nimitz)
    virtual std::shared_ptr<Unit> find_unit(const std::string &id);
};
