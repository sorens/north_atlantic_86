//
//  weapon_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/17/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "debug.hpp"
#include "file.hpp"
#include "json11.hpp"
#include "weapon_data.hpp"
#include "weapon_data_exception.hpp"
#include "weapon_system.hpp"

using namespace json11;

#pragma mark _weapon_data

const static int FIELD_NAME                 = 0;
const static int FIELD_TYPE                 = 1;
const static int FIELD_AFFILIATION          = 2;
const static int FIELD_RANGE                = 3;
const static int FIELD_AVERAGE_DAMAGE       = 4;
const static int FIELD_ACCURACY_RATING      = 5;
const static int FIELD_SURFACE_SKIMMING     = 6;
const static int FIELD_SAM_SALVO_RATE       = 7;
const static int FIELD_LRAAM_SALVO_RATE     = 8;

class _weapon_data : public weapon_data
{
    std::unordered_map<std::string, std::shared_ptr<weapon_system>> _weapon_systems;

public:
    void add_system(std::shared_ptr<weapon_system> system)
    {
        std::string key(system->name());
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        _weapon_systems[key] = system;
    }
    
    void initialize(const std::string &json_import)
    {
        if (json_import.empty())
            throw import_failed_weapon_data_exception("json data is empty");
        
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())     // TODO customize exception to accept error string
            throw import_failed_weapon_data_exception(error);
        
        Json data = json["weapons"];
        
        if (!data.is_array())
            throw new no_weapon_data_weapon_data_exception();
        
        for (auto &element : data.array_items()) {
            // each row will be an array as well
            if (!element.is_array())
                throw new import_failed_weapon_data_exception("expecting an array");
            
            std::string name = element[FIELD_NAME].string_value();                  // e.g. Harpoon
            weapon_system_type type = weapon_system_type_utility::to_enum(element[FIELD_TYPE].string_value()); // e.g. SSM
            std::string affiliation_id = element[FIELD_AFFILIATION].string_value(); // e.g. NATO
            affiliation_type affiliation_type = affiliation_type::NATO;
            if (affiliation_id == "SOVIET") {
                affiliation_type = affiliation_type::SOVIET;
            }
            int range = element[FIELD_RANGE].int_value();                           // e.g. 110
            int average_damage = element[FIELD_AVERAGE_DAMAGE].int_value();         // e.g. 4
            int accuracy_rating = element[FIELD_ACCURACY_RATING].int_value();       // e.g. 9
            bool surface_skimming = element[FIELD_SURFACE_SKIMMING].bool_value();   // e.g. true
            int sam_salvo_rate = 0;
            if (type == weapon_system_type::SAM)
                sam_salvo_rate = element[FIELD_SAM_SALVO_RATE].int_value();         // e.g. 0
            
            int lraam_salvo_rate = element[FIELD_LRAAM_SALVO_RATE].int_value();     // e.g. 0
            
            auto weapon_system = weapon_system::Make(name, type, affiliation_type, range, average_damage, accuracy_rating, surface_skimming, sam_salvo_rate, lraam_salvo_rate);
            
            add_system(weapon_system);
        }
    }
    
    std::shared_ptr<weapon_system> find_weapon_system(const std::string &id) override
    {
        std::string key(id);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (_weapon_systems.find(key) != _weapon_systems.end())
            return _weapon_systems[key];
        
        return nullptr;
    }
};

#pragma mark weapon_data

const std::string weapon_data::Import_Data(const std::string &path)
{
    // read in weapon_data.json
    std::string weapon_data;
    
    auto weapon_file = file::Make("weapon_data.json");
    
    if (weapon_file) {
        if (weapon_file->open(file_mode_open_read)) {
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
    
    runtime_assert(!weapon_data.empty());
    
    return weapon_data;
}

std::shared_ptr<weapon_data> weapon_data::Make(const std::string &json_import)
{
    auto weapon_data = std::make_shared<_weapon_data>();
    weapon_data->initialize(json_import);
    return weapon_data;
}

std::shared_ptr<weapon_system> weapon_data::find_weapon_system(const std::string &id)
{
    runtime_assert_not_reached();
}
