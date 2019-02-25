//
//  affiliation_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <string>
#include "affiliation_type.hpp"

const std::string affiliation_utility::to_string(affilation_type t)
{
    switch (t) {
        case affilation_type::UNKNOWN:
            return "UNKNOWN";
        case affilation_type::NATO:
            return "NATO";
        case affilation_type::SOVIET:
            return "SOVIET";
        case affilation_type::CONTESTED:
            return "CONTESTED";
    }
}
