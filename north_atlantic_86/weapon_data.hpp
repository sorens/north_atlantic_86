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

class WeaponData
{
public:
    static std::shared_ptr<WeaponData> Make();
    
    virtual std::shared_ptr<WeaponSystem> weapon_system(const std::string &id);
};