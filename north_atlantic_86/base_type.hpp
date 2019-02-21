//
//  base_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/21/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

typedef enum BaseType : int BaseType;
enum BaseType : int
{
    Unknown = 0,
    Port,
    Airbase,
};
