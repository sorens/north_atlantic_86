//
//  main.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "affiliation_type.hpp"
#include "json11.hpp"
#include "game.hpp"
#include "map.hpp"
#include "map_setup.hpp"
#include "mutable_unit.hpp"
#include "ship_data_exception.hpp"
#include "ship_db.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    try
    {
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
        
        // auto ship_data = R"(
        // {
        //     "ships": [
        //         ["CVN-68", "Nimitz", 0, 0, 75, 30, 72, 97, 1, "cvn", 1],
        //         ["CVN-70", "Vinson", 0, 0, 75, 30, 72, 97, 1, "cvn", 1]
        //     ]
        // }
        // )";

        // read in ship_data.json
        std::string path = "ship_data.json";
        std::string ship_data;
        struct stat ss;
        size_t size = 0;
        if (stat(path.c_str(), &ss) >= 0)
            size = ss.st_size;

        if (size > 0) {
            std::fstream file;
            file.open("ship_data.json", std::ios_base::in);
            char *buf = (char *)malloc((size + 1) * sizeof(char));
            buf[size] = '\0';
            if (file.good()) {
                // auto position_before = file.tellg();

                file.read(buf, size);
                // auto read_bytes = file.tellg() - position_before;
                // TODO runtime_assert(read_bytes == size);
                
                if (!file.good() && !file.eof()) {
                    file.close();
                    free(buf);
                    throw std::runtime_error(std::string("failed to read all of ship_data.json"));
                }
                
                ship_data = std::string(buf, size);
            }

            file.close();
            free(buf);
        }

        auto ships = ShipDB::factory(ship_data, AffiliationType::NATO);
        auto nimitz = ships->find_unit("CVN-68");
        std::cout << nimitz->description() << std::endl;
        auto ticonderoga = ships->find_unit("CG-47");
        std::cout << ticonderoga->description() << std::endl;
        
        auto setup_data = MapSetup::factory(map_data);
        auto game = Game::factory(setup_data);
        game->add_nato_player("Sally");
        game->add_soviet_player("Yuri");
        game->display_map();
        game->display_weather();
        auto map = game->map();
        auto portsmouth = map->at(2, 2);
        std::cout << portsmouth->description() << std::endl;
        auto ocean = map->at(5, 4);
        std::cout << "water_temperature at (5, 4): " << ocean->water_temperature() << std::endl;
        
        auto nimitz_mutable = MutableUnit::factory(nimitz);
        while (!nimitz_mutable->is_sunk()) {
            nimitz_mutable->apply_damage(10);
            std::cout << "Nimitz damage: " << nimitz_mutable->damage() << std::endl;
        }
        
        if (nimitz_mutable->is_sunk())
            std::cout << "The Nimitz has been sunk!" << std::endl;
        
        auto sub = ships->find_unit("SSN-V31");
        std::cout << sub->description() << std::endl;
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
