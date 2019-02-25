//
//  map_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "map_data.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "grid.hpp"
#include "grid_type.hpp"
#include "map_setup_exception.hpp"
#include "json11.hpp"
#include <cmath>
#include <vector>

#pragma mark _map_data

class _map_data : public map_data
{
    std::vector<std::shared_ptr<grid>> _data;
    
public:
    _map_data() {}
    
    void initialize(const std::string &json_import, std::shared_ptr<naval_station_data> naval_station_data)
    {
        if (json_import.empty())
            throw setup_exception();
        
        std::string error;
        auto json = json11::Json::parse(json_import, error);
        if (!json["map"].is_array())
            throw no_map_setup_exception("json 'map' is not an array");
        
        if (!json["names"].is_array())
            throw no_map_setup_exception("json 'names' is not an array");
        
        auto map = json["map"].array_items();     // array of integers
        auto names = json["names"].array_items(); // array of names
        
        if (map.empty())
            throw no_map_setup_exception("json 'map' is empty");
        
        auto map_size = map.size();
        int n = std::pow(map_size, 0.5);
        
        if (n * n != map_size)
            throw map_not_square_setup_exception();
        
        int x = 0, y = 0;
        int name_index = 0;
        
        for (auto &element : map) {
            std::string name;
            grid_type type = static_cast<grid_type>(element.int_value());
            
            if (type == grid_type::Airbase || type == grid_type::Port) {
                if (names.empty())
                    throw name_setup_exception();
                
                name = names[name_index++].string_value();
                
                if (name.length() > 32)
                    throw name_too_long_setup_exception();
            }
            
            auto grid = grid::Make(name, type, x, y, naval_station_data);
            _data.push_back(grid);
            
            x++;
            if (x >= n) {
                x = 0;
                y++;
            }
        }
    }
    
    const std::vector<std::shared_ptr<grid>> map_grid() override
    {
        return _data;
    }
};

#pragma mark map_data

const std::string map_data::Import_Data(const std::string &path)
{
    // read in map_data.json
    std::string data;
    
    auto file = file::Make("map_data.json");
    
    if (file) {
        if (file->open(file_mode_open_read)) {
            auto size = file->size();
            if (size > 0) {
                char *buf = (char *)malloc((size + 1) * sizeof(char));
                buf[size] = '\0';
                
                auto read_bytes = file->read(buf, size);
                runtime_assert(read_bytes == size);
                
                data = std::string(buf, size);
                
                file->close();
                free(buf);
            }
        }
    }
    
    runtime_assert(!data.empty());
    
    return data;
}

std::shared_ptr<map_data> map_data::Make(const std::string &json_import, std::shared_ptr<naval_station_data> naval_station_data)
{
    auto map_data = std::make_shared<_map_data>();
    map_data->initialize(json_import, naval_station_data);
    return map_data;
}

const std::vector<std::shared_ptr<grid>> map_data::map_grid()
{
    runtime_assert_not_reached();
}
