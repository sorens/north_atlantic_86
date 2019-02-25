//
//  map_display_ascii.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "debug.hpp"
#include "map_display_ascii.hpp"
#include <cmath>

#pragma mark MapDisplayAscii

int MapDisplayAscii::ConvertCoordinates(const int x, const int y)
{
    // TODO hard-coded
    return (y * 40) + x;
}

std::ostringstream MapDisplayAscii::Generate(std::shared_ptr<game> game)
{
    auto grid = game->map()->grids();
    auto size = grid.size();
    int side = std::pow(size, 0.5);
    
    std::vector<char> map(size);
    
    int i = 0;
    
    // place all grid objects
    for (auto g : grid) {
        switch (g->type()) {
            case grid_type::Landmass:
                map[i] = '*';
                break;
            case grid_type::Ocean:
                map[i] = '-';
                break;
            case grid_type::Airbase:
            case grid_type::Port:
                map[i] = g->station()->name()[0];
                break;
            case grid_type::Unknown:
                break;
        }
        
        ++i;
    }

    // TODO
    
    
    // place all NATO fleet objects
    auto nato_tfs = game->player_nato()->task_forces();
    
    for (auto &tf : nato_tfs) {
        logverbose(tf->description());
    }
    
    // place all SOVIET fleet objects
    auto soviet_tfs = game->player_soviet()->task_forces();
    
    for (auto &tf : soviet_tfs) {
        logverbose(tf->description());
    }
    
    std::ostringstream ss;
    
    ss << "NATO: " << game->player_nato()->name() << "                     SOVIET: " << game->player_soviet()->name() << std::endl;
    ss << "|==================================== M A P ====================================|" << std::endl;
    ss << "|";
    
    for (int j = 1; j < size+1; ++j) {
        ss << map[j-1];
        if (j % side == 0) {
            ss << "|" << std::endl << "|";
        }
        else {
            ss << " ";
        }
    }
    
    ss << "===============================================================================|" << std::endl;
    
    return ss;
}
