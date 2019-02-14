//
//  ship_db.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include "affiliation_type.hpp"
#include "unit.hpp"

class ShipDB
{
public:
    // return a ship_data
    static std::shared_ptr<ShipDB> factory(const std::string &json_import, AffiliationType affiliation);
    
    // find a ship by it's id (e.g. CVN-68 is the USS Nimitz)
    virtual std::shared_ptr<Unit> find_unit(const std::string &id);
};
