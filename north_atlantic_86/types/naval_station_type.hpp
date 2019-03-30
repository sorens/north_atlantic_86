//
//  naval_station_type.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/21/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

typedef enum naval_station_type : int naval_station_type;
enum naval_station_type : int
{
    Unknown = 0,
    Port,
    Airbase,
};
