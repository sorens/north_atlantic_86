//
//  main.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "affiliation_type.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "game.hpp"
#include "json11.hpp"
#include "log.hpp"
#include "map.hpp"
#include "map_display_ascii.hpp"
#include "map_setup.hpp"
#include "ship_data_exception.hpp"
#include "ship_data.hpp"
#include "weapon_data.hpp"

#include "tests.hpp"

#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "task_force.hpp"

int main(int argc, const char * argv[]) {
    
    try
    {
        auto tests = Tests::Make();
        tests->task_force_unit_test();
        
//        loginfo("********* GAME STARTING *********");
//        
//        // read in map data
//        std::string map_data = MapSetup::Import_Data("map_data.json");
//        
//        // read in ship_data.json
//        std::string ship_data = ShipData::Import_Data("ship_data.json");
//       
//        // read in weapon_data.json
//        std::string weapon_data = WeaponData::Import_Data("weapon_data.json");
//        
//        auto setup_data = MapSetup::factory(map_data);
//        auto game = Game::Make(setup_data, ship_data, weapon_data);
//        game->add_nato_player("Sally");
//        game->add_soviet_player("Yuri");
//        auto display = MapDisplayAscii::Generate(game);
//        std::cout << display.str();
//
//        // take a turn
//        game->next_turn();
    }
    catch(ship_data_exception &e)
    {
        std::cout << "ship_data_exception => '" << e.what() << "'" << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "std::exception => '" << e.what() << "'" << std::endl;
    }
    catch(...)
    {
        std::cout << "unhandled exception" << std::endl;
    }
    
    return 0;
}
