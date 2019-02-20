//
//  ship_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "debug.hpp"
#include "file.hpp"
#include "json11.hpp"
#include "ship_data.hpp"
#include "ship_data_exception.hpp"
#include "unit.hpp"

using namespace json11;

#pragma mark _ShipData

class _ShipData : public ShipData
{
public:
    _ShipData() {}
    
    void initialize(const std::string &json_import) 
    {
        if (json_import.empty())
            throw import_failed_ship_data_exception();
            
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())     // TODO customize exception to accept error string
            throw import_failed_ship_data_exception();
        
        Json data = json["ships"];
        
        if (!data.is_array())
            throw new no_ship_data_ship_data_exception();
            
        for (auto &element : data.array_items()) {
            // each row will be an array as well
            if (!element.is_array())
                throw new import_failed_ship_data_exception();
                
            std::string id = element[0].string_value();                 // e.g. CVN-68
            std::string name = element[1].string_value();               // e.g. Nimitz
            int main_gun = element[2].int_value();                      // e.g. 0
            int aa_gun = element[3].int_value();                        // e.g. 0
            int missile_def = element[4].int_value();                   // e.g. 75
            int max_speed = element[5].int_value();                     // e.g. 30
            int cargo_capacity = element[6].int_value();                // e.g. 72
            int defense_factor = element[7].int_value();                // e.g. 97
            int class_id = element[8].int_value();                      // e.g. 1
            std::string ship_prefix = element[9].string_value();        // e.g. cvn
            std::string unit_class = element[10].string_value();        // e.g. Nimitz  // TODO incorporate unit_class
            std::string affiliation_id = element[11].string_value();    // e.g. NATO
            
            AffiliationType affiliation_type = AffiliationType::NATO;
            if (affiliation_id == "USSR") {
                affiliation_type = AffiliationType::SOVIET;
            }
            
            // TODO look up class_id and convert to enumerated unit_class
            auto ship = Unit::Make(id, name, UnitType::Ship, unit_class, ship_prefix, class_id, main_gun, aa_gun, missile_def, max_speed, cargo_capacity, defense_factor, affiliation_type);
            
            if (_data.find(id) != _data.end())
                throw duplicate_id_ship_data_exception(id);

            _data.insert(std::make_pair(id, ship));
        }
    }
    
    std::shared_ptr<Unit> find_unit(const std::string &id) override
    {
        if (_data.find(id) != _data.end()) {
            return _data[id];
        }
        
        return nullptr;
    }
    
private:
    std::unordered_map<std::string, std::shared_ptr<Unit>> _data;
};

std::shared_ptr<ShipData> ShipData::factory(const std::string &json_import)
{
    auto ship_data = std::make_shared<_ShipData>();
    ship_data->initialize(json_import);
    return ship_data;
}

std::shared_ptr<Unit> ShipData::find_unit(const std::string &id)
{
    return nullptr;
}

const std::string ShipData::Import_Data(const std::string &path)
{
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
    
    runtime_assert(!ship_data.empty());

    return ship_data;
}
