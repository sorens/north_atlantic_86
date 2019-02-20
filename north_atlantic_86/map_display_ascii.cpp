//
//  map_display_ascii.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "map_display_ascii.hpp"
#include <cmath>

#pragma mark MapDisplayAscii

std::ostringstream MapDisplayAscii::Generate(std::shared_ptr<Game> game)
{
    std::ostringstream ss;
    
    ss << "NATO: " << game->player_nato()->name() << "                     SOVIET: " << game->player_soviet()->name() << std::endl;
    ss << "|==================================== M A P ====================================|" << std::endl;
    ss << "|";
    auto grid = game->map()->grid();
    auto size = grid.size();
    int side = std::pow(size, 0.5);
    
    int i = 0;
    for (auto g : grid) {
        switch (g->type()) {
            case GridType::Landmass:
                ss << "*";
                break;
            case GridType::Ocean:
                ss << "_";
                break;
            case GridType::Airbase:
            case GridType::Port:
                ss << g->name()[0];
                break;
            case GridType::Unknown:
                break;
        }
        
        ++i;
        if (i % side == 0) {
            i = 0;
            ss << "|";
            ss << std::endl;
            ss << "|";
        }
        else {
             ss << " ";
        }
    }
    
    ss << "===============================================================================|" << std::endl;
    
    return ss;
}
