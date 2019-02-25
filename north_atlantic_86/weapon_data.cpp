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

#pragma mark _WeaponData

const static int FIELD_NAME                 = 0;
const static int FIELD_TYPE                 = 1;
const static int FIELD_AFFILIATION          = 2;
const static int FIELD_RANGE                = 3;
const static int FIELD_AVERAGE_DAMAGE       = 4;
const static int FIELD_ACCURACY_RATING      = 5;
const static int FIELD_SURFACE_SKIMMING     = 6;
const static int FIELD_SAM_SALVO_RATE       = 7;
const static int FIELD_LRAAM_SALVO_RATE     = 8;

class _WeaponData : public WeaponData
{
    std::unordered_map<std::string, std::shared_ptr<WeaponSystem>> _weapon_systems;

public:
    void add_system(std::shared_ptr<WeaponSystem> system)
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
            WeaponSystemType type = WeaponSystemTypeUtility::to_enum(element[FIELD_TYPE].string_value()); // e.g. SSM
            std::string affiliation_id = element[FIELD_AFFILIATION].string_value(); // e.g. NATO
            affilation_type affiliation_type = affilation_type::NATO;
            if (affiliation_id == "SOVIET") {
                affiliation_type = affilation_type::SOVIET;
            }
            int range = element[FIELD_RANGE].int_value();                           // e.g. 110
            int average_damage = element[FIELD_AVERAGE_DAMAGE].int_value();         // e.g. 4
            int accuracy_rating = element[FIELD_ACCURACY_RATING].int_value();       // e.g. 9
            bool surface_skimming = element[FIELD_SURFACE_SKIMMING].bool_value();   // e.g. true
            int sam_salvo_rate = 0;
            if (type == WeaponSystemType::SAM)
                sam_salvo_rate = element[FIELD_SAM_SALVO_RATE].int_value();         // e.g. 0
            
            int lraam_salvo_rate = element[FIELD_LRAAM_SALVO_RATE].int_value();     // e.g. 0
            
            auto weapon_system = WeaponSystem::Make(name, type, affiliation_type, range, average_damage, accuracy_rating, surface_skimming, sam_salvo_rate, lraam_salvo_rate);
            
            add_system(weapon_system);
        }
    }
    
    std::shared_ptr<WeaponSystem> weapon_system(const std::string &id) override
    {
        std::string key(id);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (_weapon_systems.find(key) != _weapon_systems.end())
            return _weapon_systems[key];
        
        return nullptr;
    }
};

#pragma mark WeaponData

const std::string WeaponData::Import_Data(const std::string &path)
{
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
    
    runtime_assert(!weapon_data.empty());
    
    return weapon_data;
}

std::shared_ptr<WeaponData> WeaponData::Make(const std::string &json_import)
{
    auto weapon_data = std::make_shared<_WeaponData>();
    weapon_data->initialize(json_import);
    return weapon_data;
}

std::shared_ptr<WeaponSystem> WeaponData::weapon_system(const std::string &id)
{
    return nullptr;
}
