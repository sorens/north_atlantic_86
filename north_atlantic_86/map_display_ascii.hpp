//
//  map_display_ascii.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <sstream>
#include <vector>
#include "game.hpp"

class MapDisplayAscii
{
public:
    // Convert game coordinates to a storage index
    static int ConvertCoordinates(const int x, const int y);
    
    // Generate a stream containing the consolidated map
    static std::ostringstream Generate(std::shared_ptr<Game> game);
};
