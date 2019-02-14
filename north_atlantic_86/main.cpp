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
#include "ship_db.hpp"
#include <iostream>

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
        
        auto ship_data = R"(
        {
            "ships": [
                ["CVN-68", "Nimitz", 0, 0, 75, 30, 72, 97, 1, "cvn", 1],
                ["CVN-70", "Vinson", 0, 0, 75, 30, 72, 97, 1, "cvn", 1]
            ]
        }
        )";
        
        auto ships = ShipDB::factory(ship_data, AffiliationType::NATO);
        auto nimitz = ships->find_unit("CVN-68");
        std::cout << nimitz->description() << std::endl;
        
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
    }
    catch(std::exception &e)
    {
        std::cerr << "error! '" << e.what() << "'" << std::endl;
    }
    
    return 0;
}
