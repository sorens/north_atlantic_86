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
#include "map_setup.hpp"
#include "ship_data_exception.hpp"
#include "ship_data.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    
    try
    {
        loginfo("********* GAME STARTING *********");
        
        // read in map data
        std::string map_data;
        
        auto map_file = File::Make("map_data.json");
        
        if (map_file) {
            if (map_file->open(FileModeOpenRead)) {
                auto size = map_file->size();
                if (size > 0) {
                    char *buf = (char *)malloc((size + 1) * sizeof(char));
                    buf[size] = '\0';
                    
                    auto read_bytes = map_file->read(buf, size);
                    runtime_assert(read_bytes == size);
                    
                    map_data = std::string(buf, size);
                    
                    map_file->close();
                    free(buf);
                }
            }
        }
        
        // read in ship_data.json
        std::string ship_data;
        
        auto ship_file = File::Make("ship_data.json");
        
        if (ship_file) {
            if (ship_file->open(FileModeOpenRead)) {
                auto size = ship_file->size();
                if (size > 0) {
                    char *buf = (char *)malloc((size + 1) * sizeof(char));
                    buf[size] = '\0';
                    
                    auto read_bytes = ship_file->read(buf, size);
                    runtime_assert(read_bytes == size);
                    
                    ship_data = std::string(buf, size);
                    
                    ship_file->close();
                    free(buf);
                }
            }
        }
        
        if (ship_data.empty())
            runtime_assert_not_reached();
        
        // read in weapon_data.json
        std::string weapon_data;
        auto weapon_file = File::Make("weapon_data.json");
        
        if (weapon_file) {
            if (weapon_file->open(FileModeOpenRead)) {
                auto size = weapon_file->size();
                if (size > 0) {
                    char *buf = (char *)malloc((size + 1) * sizeof(char));
                    buf[size] = '\0';
                    
                    auto read_bytes = weapon_file->read(buf, size);
                    runtime_assert(read_bytes == size);
                    
                    weapon_data = std::string(buf, size);
                    
                    weapon_file->close();
                    free(buf);
                }
            }
        }
        
        if (weapon_data.empty())
            runtime_assert_not_reached();
        
        auto setup_data = MapSetup::factory(map_data);
        auto game = Game::Make(setup_data, ship_data, weapon_data);
        game->add_nato_player("Sally");
        game->add_soviet_player("Yuri");
        game->display_map();
        game->display_weather();

        // take a turn
        game->next_turn();
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
