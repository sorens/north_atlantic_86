//
//  affiliation_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <string>
#include "affiliation_type.hpp"

const std::string AffiliationUtility::to_string(AffiliationType t)
{
    switch (t) {
        case AffiliationType::UNKNOWN:
            return "UNKNOWN";
        case AffiliationType::NATO:
            return "NATO";
        case AffiliationType::SOVIET:
            return "SOVIET";
    }
}
