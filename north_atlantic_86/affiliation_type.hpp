//
//  affiliation_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <string>

enum class AffiliationType : int
{
    UNKNOWN = -1,
    NATO,
    SOVIET
};
    
class AffiliationUtility
{
public:
    static const std::string to_string(AffiliationType t);
};
