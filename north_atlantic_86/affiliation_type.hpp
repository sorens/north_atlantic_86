//
//  affiliation_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class affiliation_type : int
{
    UNKNOWN = -1,
    NATO,
    SOVIET,
    CONTESTED
};
    
class affiliation_utility
{
public:
    static const std::string to_string(affiliation_type t);
};
