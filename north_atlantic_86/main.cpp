//
//  main.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "json.hpp"
#include "game.hpp"
#include "map.hpp"
#include "map_setup.hpp"
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
    }
    catch(std::exception &e)
    {
        std::cerr << "error! '" << e.what() << "'" << std::endl;
    }
    
    return 0;
}
