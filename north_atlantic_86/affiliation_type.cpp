//
//  affiliation_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <string>
#include "affiliation_type.hpp"

const std::string affiliation_utility::to_string(affiliation_type t)
{
    switch (t) {
        case affiliation_type::UNKNOWN:
            return "UNKNOWN";
        case affiliation_type::NATO:
            return "NATO";
        case affiliation_type::SOVIET:
            return "SOVIET";
        case affiliation_type::CONTESTED:
            return "CONTESTED";
    }
}
