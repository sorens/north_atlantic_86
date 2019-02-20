//
//  weapon_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/17/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "json11.hpp"
#include "weapon_data.hpp"
#include "weapon_data_exception.hpp"
#include "weapon_system.hpp"

using namespace json11;

#pragma mark _WeaponData

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
            
            std::string name = element[0].string_value();               // e.g. Harpoon
            WeaponSystemType type = WeaponSystemTypeUtility::to_enum(element[1].string_value()); // e.g. SSM
            std::string affiliation_id = element[2].string_value();     // e.g. NATO
            AffiliationType affiliation_type = AffiliationType::NATO;
            if (affiliation_id == "USSR") {
                affiliation_type = AffiliationType::SOVIET;
            }
            int range = element[3].int_value();                         // e.g. 110
            int average_damage = element[4].int_value();                // e.g. 4
            int accuracy_rating = element[5].int_value();               // e.g. 9
            bool surface_skimming = element[6].bool_value();            // e.g. true
            int sam_salvo_rate = 0;
            if (type == WeaponSystemType::SAM)                          // e.g. 0
                sam_salvo_rate = element[7].int_value();
            
            auto weapon_system = WeaponSystem::Make(name, type, affiliation_type, range, average_damage, accuracy_rating, surface_skimming, sam_salvo_rate);
            
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
