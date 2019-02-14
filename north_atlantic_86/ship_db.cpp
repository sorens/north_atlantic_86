//
//  ship_db.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "json11.hpp"
#include "ship_db.hpp"
#include "unit.hpp"

using namespace json11;

class _ShipDB : public ShipDB
{
public:
    _ShipDB() {}
    
    void initialize(const std::string &json_import, AffiliationType affiliation) 
    {
        if (json_import.empty())
            throw new import_failed_ship_data_exception();
            
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())     // TODO customize exception to accept error string
            throw new import_failed_ship_data_exception();
        
        Json data = json["ships"];
        
        if (!data.is_array())
            throw new no_ship_data_ship_data_exception();
            
        for (auto &element : data.array_items()) {
            // each row will be an array as well
            if (!element.is_array())
                throw new import_failed_ship_data_exception();
                
            std::string id = element[0].string_value();             // e.g. CVN-68
            std::string name = element[1].string_value();           // e.g. Nimitz
            int main_gun = element[2].int_value();                  // e.g. 0
            int aa_gun = element[3].int_value();                    // e.g. 0
            int missile_def = element[4].int_value();               // e.g. 75
            int max_speed = element[5].int_value();                 // e.g. 30
            int cargo_capacity = element[6].int_value();            // e.g. 72
            int defense_factor = element[7].int_value();            // e.g. 97
            int class_id = element[8].int_value();                  // e.g. 1
            std::string unit_class = element[9].string_value();     // e.g. cvn
            int affiliation_id = element[10].int_value();            // e.g. 1
            
            // TODO look up class_id and convert to enumerated unit_class
            auto ship = Unit::factory(id, name, UnitType::Ship, unit_class, class_id, main_gun, aa_gun, missile_def, max_speed, cargo_capacity, defense_factor, static_cast<AffiliationType>(affiliation_id));
            
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

std::shared_ptr<ShipDB> ShipDB::factory(const std::string &json_import, AffiliationType affiliation)
{
    auto ship_data = std::make_shared<_ShipDB>();
    ship_data->initialize(json_import, affiliation);
    return ship_data;
}

std::shared_ptr<Unit> ShipDB::find_unit(const std::string &id)
{
    return nullptr;
}
