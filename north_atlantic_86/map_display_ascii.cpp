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

int MapDisplayAscii::ConvertCoordinates(const int x, const int y)
{
    // TODO hard-coded
    return (y * 40) + x;
}

std::ostringstream MapDisplayAscii::Generate(std::shared_ptr<Game> game)
{
    auto grid = game->map()->grid();
    auto size = grid.size();
    int side = std::pow(size, 0.5);
    
    std::vector<char> map(size);
    
    int i = 0;
    
    // place all grid objects
    for (auto g : grid) {
        switch (g->type()) {
            case GridType::Landmass:
                map[i] = '*';
                break;
            case GridType::Ocean:
                map[i] = '-';
                break;
            case GridType::Airbase:
            case GridType::Port:
                map[i] = g->name()[0];
                break;
            case GridType::Unknown:
                break;
        }
        
        ++i;
    }

    // TODO
    
    
    // place all NATO fleet objects
//    auto nato_fleets = game->player_nato()->fleets();
//    
//    for (auto &fleet : nato_fleets) {
//    }
    
    // place all SOVIET fleet objects
//    auto soviet_fleets = game->player_soviet()->fleets();
//    
//    for (auto &fleet : soviet_fleets) {
//    }
    
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