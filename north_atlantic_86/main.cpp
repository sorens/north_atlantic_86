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
#include "mutable_unit.hpp"
#include "ship_data_exception.hpp"
#include "ship_data.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    
    try
    {
        loginfo("********* GAME STARTING *********");
        auto map_data = R"(
        {
            "map": [0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
                    0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
                    0, 0, 3, 1, 1, 1, 1, 1, 0, 2,
                    0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                    1, 1, 1, 1, 2, 0, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            "names": ["Portsmouth", 
                      "Halifax",
                      "Centersville"]
        }
        )";
        
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
        
        auto ships = ShipData::factory(ship_data);
        logverbose(ships->find_unit("CG-47")->description());
        auto nimitz = ships->find_unit("CVN-68");
        logverbose(nimitz->description());
        
        auto setup_data = MapSetup::factory(map_data);
        auto game = Game::factory(setup_data);
        game->add_nato_player("Sally");
        game->add_soviet_player("Yuri");
        game->display_map();
        game->display_weather();
        auto map = game->map();
        auto portsmouth = map->at(2, 2);
        logverbose(portsmouth->description());
        auto ocean = map->at(5, 4);
        logverbose("water temperature at (5, 4): " << ocean->water_temperature());
        
        auto nimitz_mutable = MutableUnit::factory(nimitz);
        while (!nimitz_mutable->is_sunk()) {
            nimitz_mutable->apply_damage(10);
            loginfo("Nimitz damage: " << nimitz_mutable->damage());
        }
        
        if (nimitz_mutable->is_sunk())
            loginfo("The Nimitz has been sunk!");
        
        auto sub = ships->find_unit("SSN-V31");
        loginfo(ships->find_unit("SSN-V31")->description());
        
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
