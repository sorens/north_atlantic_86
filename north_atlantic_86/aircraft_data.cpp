//
//  aircraft_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/22/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "aircraft_data.hpp"
#include "aircraft_data_exception.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "json11.hpp"
#include <unordered_map>

using namespace json11;

#pragma mark _aircraft_data

class _aircraft_data : public aircraft_data
{
public:
    _aircraft_data() {}
    
    void add_aircraft(std::shared_ptr<aircraft> aircraft)
    {
        std::string key(aircraft->designation());
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        _data[key] = aircraft;
    }

    void initialize(const std::string &json_import, std::shared_ptr<weapon_data> weapons_data)
    {
        runtime_assert(weapons_data);
        
        if (json_import.empty())
            throw import_failed_aircraft_data_exception();
        
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())     // TODO customize exception to accept error string
            throw import_failed_aircraft_data_exception();
        
        Json data = json["aircrafts"];
        
        if (!data.is_array())
            throw new no_aircraft_data_aircraft_data_exception();
        
        for (auto &element : data.array_items()) {
            // each row will be an array as well
            if (!element.is_array())
                throw new import_failed_aircraft_data_exception();
            
            std::string name = element[0].string_value();
            std::string designation = element[1].string_value();
            int range = element[2].int_value();
            // TODO inject weapon_data
            std::shared_ptr<weapon_system> weapon_system;
            std::string weapon_system_key = element[3].string_value();
            if (!weapon_system_key.empty())
                weapon_system = weapons_data->find_weapon_system(weapon_system_key);
            bool is_carrier_aircraft = element[4].bool_value();
            affilation_type affiliation = affilation_type::NATO;
            if (element[5].string_value() == "SOVIET")
                affiliation = affilation_type::SOVIET;
            
            int ecm_rating = element[6].int_value();
            int dogfighting_rating = element[7].int_value();
            int bomber_accuracy = element[8].int_value();
            int radar_capability = element[9].int_value();
            
            int lrcap_missile_ew_avg = element[10].int_value();
            int lrcap_missile_ew_max = element[11].int_value();
            int lrcap_missile_avg = element[12].int_value();
            int lrcap_missile_max = element[13].int_value();
            int lrcap_dogfight_ew_avg = element[14].int_value();
            int lrcap_dogfight_ew_max = element[15].int_value();
            int lrcap_dogfight_avg = element[16].int_value();
            int lrcap_dogfight_max = element[17].int_value();
            int cap_missile_ew_avg = element[18].int_value();
            int cap_missile_ew_max = element[19].int_value();
            int cap_missile_avg = element[20].int_value();
            int cap_missile_max = element[21].int_value();
            int cap_dogfight_ew_avg = element[22].int_value();
            int cap_dogfight_ew_max = element[23].int_value();
            int cap_dogfight_avg = element[24].int_value();
            int cap_dogfight_max = element[25].int_value();
            
            auto aircraft = aircraft::Make(name, designation, range, weapon_system, is_carrier_aircraft, affiliation, ecm_rating, dogfighting_rating, bomber_accuracy, radar_capability, lrcap_missile_ew_avg, lrcap_missile_ew_max, lrcap_missile_avg, lrcap_missile_max, lrcap_dogfight_ew_avg, lrcap_dogfight_ew_max, lrcap_dogfight_avg, lrcap_dogfight_max, cap_missile_ew_avg, cap_missile_ew_max, cap_missile_avg, cap_missile_max, cap_dogfight_ew_avg, cap_dogfight_ew_max, cap_dogfight_avg, cap_dogfight_max);
            
            add_aircraft(aircraft);
        }
    }

    std::shared_ptr<aircraft> find_aircraft(const std::string &id) override
    {
        std::string key(id);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (_data.find(key) != _data.end()) {
            return _data[key];
        }
        
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<aircraft>> _data;
};

#pragma mark aircraft_data

std::shared_ptr<aircraft_data> aircraft_data::Make(const std::string &json_import, std::shared_ptr<weapon_data> weapons_data)
{
    auto aircraft_data = std::make_shared<_aircraft_data>();
    aircraft_data->initialize(json_import, weapons_data);
    return aircraft_data;
}

std::shared_ptr<aircraft> aircraft_data::find_aircraft(const std::string &id)
{
    runtime_assert_not_reached();
}

const std::string aircraft_data::Import_Data(const std::string &path)
{
    // read in aircraft_data.json
    std::string aircraft_data;
    
    auto aircraft_file = file::Make("aircraft_data.json");
    
    if (aircraft_file) {
        if (aircraft_file->open(file_mode_open_read)) {
            auto size = aircraft_file->size();
            if (size > 0) {
                char *buf = (char *)malloc((size + 1) * sizeof(char));
                buf[size] = '\0';
                
                auto read_bytes = aircraft_file->read(buf, size);
                runtime_assert(read_bytes == size);
                
                aircraft_data = std::string(buf, size);
                
                aircraft_file->close();
                free(buf);
            }
        }
    }
    
    runtime_assert(!aircraft_data.empty());

    return aircraft_data;
}
