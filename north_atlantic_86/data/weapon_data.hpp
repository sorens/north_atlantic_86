//
//  weapon_data.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/17/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <memory>
#include "weapon_system.hpp"

class weapon_data
{
public:
    
    static const std::string Import_Data(const std::string &path);
    
    static std::shared_ptr<weapon_data> Make(const std::string &json_import);
    
    virtual std::shared_ptr<weapon_system> find_weapon_system(const std::string &id);
};
