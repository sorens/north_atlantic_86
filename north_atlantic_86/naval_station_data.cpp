//
//  naval_station_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/24/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "debug.hpp"
#include "file.hpp"
#include "json11.hpp"
#include "naval_station.hpp"
#include "naval_station_data.hpp"
#include "naval_station_data_exception.hpp"

using namespace json11;

#pragma mark _naval_station_data

class _naval_station_data : public naval_station_data
{
private:
    std::unordered_map<std::string, std::shared_ptr<naval_station>> _data;

public:
    _naval_station_data() {}
    
    void initialize(const std::string &json_import, std::shared_ptr<weapon_data> weapon_data)
    {
        if (json_import.empty())
            throw import_failed_naval_station_data_exception();
        
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())
            throw no_naval_station_data_naval_station_data_exception();
        
        Json data = json["naval_stations"];
        
        for (auto &element : data.array_items()) {
            // each row will be an array as well
            if (!element.is_array())
                throw import_failed_naval_station_data_exception();
            
            // TODO import
            std::string name = element[0].string_value();
            std::string type_string = element[1].string_value();
            
            naval_station_type type = naval_station_type::Airbase;
            if (type_string == "PORT")
                type = naval_station_type::Port;
            
            std::string affiliation_string = element[2].string_value();
            
            affilation_type affiliation_type = affilation_type::NATO;
            if (affiliation_string == "SOVIET") {
                affiliation_type = affilation_type::SOVIET;
            }
            else if (affiliation_string == "CONTESTED") {
                affiliation_type = affilation_type::CONTESTED;
            }
            
            int main_guns = element[3].int_value();
            int light_guns = element[4].int_value();
            int missile_defense = element[5].int_value();
            int airbase_capacity = element[6].int_value();
            int defense_factor = element[7].int_value();
            std::shared_ptr<WeaponSystem> ssm;
            std::shared_ptr<WeaponSystem> asw;
            std::shared_ptr<WeaponSystem> sam;
            std::shared_ptr<WeaponSystem> ast;
            int ssm_salvo_rate = 0;
            int ssm_magazine_capacity = 0;
            std::string ssm_string = element[8].string_value();
            if (!ssm_string.empty()) {
                // match up SSM weapon system
                ssm_salvo_rate = element[9].int_value();
                ssm_magazine_capacity = element[10].int_value();
            }
            
            std::string asw_string = element[11].string_value();
            if (!asw_string.empty()) {
                // TODO match up ASW wapon system
            }
            
            std::string sam_string = element[12].string_value();
            if (!sam_string.empty()) {
                // TODO match up SAM wapon system
            }
            
            std::string ast_string = element[13].string_value();
            if (!ast_string.empty()) {
                // TODO match up AST wapon system
            }
            
            int helicopters = element[14].int_value();
            int ew_strength = element[15].int_value();
            int sonar_strength = element[16].int_value();

            
            auto naval_station = naval_station::Make(name, affiliation_type, type, airbase_capacity, light_guns, defense_factor, ew_strength, helicopters, main_guns, missile_defense, sonar_strength, ssm, ssm_salvo_rate, ssm_magazine_capacity, asw, sam, ast);

            std::string key(name);
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            _data.insert(std::make_pair(key, naval_station));
        }
    }
    
    std::shared_ptr<naval_station> find_naval_station(const std::string &name) override
    {
        std::string key(name);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (_data.find(key) != _data.end()) {
            return _data[key];
        }
        
        return nullptr;
    }
};

#pragma mark naval_station_data

std::shared_ptr<naval_station> naval_station_data::find_naval_station(const std::string &name)
{
    runtime_assert_not_reached();
}

// import JSON data
const std::string naval_station_data::Import_Data(const std::string &path)
{
    // read in naval_station.json
    std::string naval_stattion_data;
    
    auto file = File::Make("naval_station_data.json");
    
    if (file) {
        if (file->open(FileModeOpenRead)) {
            auto size = file->size();
            if (size > 0) {
                char *buf = (char *)malloc((size + 1) * sizeof(char));
                buf[size] = '\0';
                
                auto read_bytes = file->read(buf, size);
                runtime_assert(read_bytes == size);
                
                naval_stattion_data = std::string(buf, size);
                
                file->close();
                free(buf);
            }
        }
    }
    
    runtime_assert(!naval_stattion_data.empty());
    
    return naval_stattion_data;
}

// return naval_station data
std::shared_ptr<naval_station_data> naval_station_data::Make(const std::string &json_import, std::shared_ptr<weapon_data> weapon_data)
{
    auto naval_station_data = std::make_shared<_naval_station_data>();
    naval_station_data->initialize(json_import, weapon_data);
    return naval_station_data;
}
