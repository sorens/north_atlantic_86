//
//  main.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "aircraft_data.hpp"
#include "affiliation_type.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "game.hpp"
#include "json11.hpp"
#include "log.hpp"
#include "map.hpp"
#include "map_display_ascii.hpp"
#include "map_setup.hpp"
#include "naval_station_data.hpp"
#include "naval_station_data_exception.hpp"
#include "ship_data_exception.hpp"
#include "ship_data.hpp"
#include "weapon_data.hpp"

#include "argh.h"
#include "tests.hpp"

#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "task_force.hpp"

void play_game()
{
    try
    {
        loginfo("********* GAME STARTING *********");
        
        // read in map data
        std::string map_data = MapSetup::Import_Data("map_data.json");
        
        // read in ship_data.json
        std::string ship_data = ShipData::Import_Data("ship_data.json");
       
        // read in weapon_data.json
        std::string weapon_data = WeaponData::Import_Data("weapon_data.json");
        
        // read in aircraft_data.json
        std::string aircraft_data = aircraft_data::Import_Data("aircraft_data.json");
        
        // read in naval_station_data.json
        std::string naval_station_data = naval_station_data::Import_Data("naval_station_data.json");
        
        auto game = Game::Make(map_data, ship_data, weapon_data, aircraft_data, naval_station_data);
        game->add_nato_player("Sally");
        game->add_soviet_player("Yuri");

        // take a turn
        game->next_turn();

        auto display = MapDisplayAscii::Generate(game);
        std::cout << display.str();
    }
    catch(ship_data_exception &e)
    {
        logerror("ship_data_exception => '" << e.what() << "'");
    }
    catch(std::exception &e)
    {
        logerror("std::exception => '" << e.what() << "'");
    }
    catch(...)
    {
        logerror("unhandled exception");
    }
}

void print_help()
{
    std::cout << "North Atlantic '86 (© Stephen Orens, 2019)" << std::endl;
    std::cout << "A recreation of the famous Gary Grigsby game!" << std::endl;
    std::cout << "usage: north_atlantic_86 -u|-p" << std::endl;
    std::cout << "        -u, --unit_tests        run the unit tests" << std::endl;
    std::cout << "        -p, --play_game         play the game" << std::endl;
}

void run_unit_tests()
{
    try
    {
       Tests::Make()->test_all();
    }
    catch(...)
    {
        logerror("unhandled exception");
    }
}

int main(int argc, const char * argv[]) {

    argh::parser cmdl(argc, argv);
    
    if (cmdl[{"-u", "--unit-tests"}]) {
        run_unit_tests();
        return 0;
    }
    
    if (cmdl[{"-p", "--play"}]) {
        play_game();
        return 0;
    }
    
    if (cmdl[{"-h", "-?", "--help"}]) {
        print_help();
        return 0;
    }
    
    print_help();
    return 0;
}
