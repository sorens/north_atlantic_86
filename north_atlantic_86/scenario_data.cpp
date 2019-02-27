//
//  scenario_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/25/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "scenario_data.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "json11.hpp"
#include "exception.hpp"    // temp
#include "pipeline.hpp"
#include "task_force.hpp"
#include "unit.hpp"

using namespace json11;

struct station_data
{
    std::string name;
    std::string station_id;
    int supplies;
    int infantry;
    
    station_data()
    {
    }
    
    station_data(const std::string id, const std::string n, const int s, const int i) :
    station_id(id), name(n), supplies(s), infantry(i)
    {
    }
    
    station_data(const station_data &other) :
    station_id(other.station_id), name(other.name), supplies(other.supplies), infantry(other.infantry)
    {
    }
};

class _scenario_data : public scenario_data
{
    std::unordered_map<std::string, std::shared_ptr<pipeline>> _nato_pipeline;
    std::unordered_map<std::string, std::shared_ptr<pipeline>> _soviet_pipeline;
    std::unordered_map<std::string, station_data> _nato_ports;
    std::unordered_map<std::string, station_data> _soviet_ports;
    std::unordered_map<std::string, station_data> _nato_airbases;
    std::unordered_map<std::string, station_data> _soviet_airbases;
    std::unordered_map<std::string, std::shared_ptr<task_force>> _nato_task_forces;
    std::unordered_map<std::string, std::shared_ptr<task_force>> _soviet_task_forces;
    
public:
    _scenario_data() {}
    
    void initialize(const std::string &json_import, std::shared_ptr<ShipData> ship_data)
    {
        if (json_import.empty())
            throw na_exception("json data is empty");
        
        std::string error;
        auto json = Json::parse(json_import, error);
        if (!error.empty())     // TODO customize exception to accept error string
            throw na_exception(error);
        
        Json data = json["scenario"];
        
        if (!data.is_object())
            throw new na_exception();
        
        auto nato_pipeline_json = data["nato_pipeline"];
        if (nato_pipeline_json.is_object()) {
            for (auto &obj : nato_pipeline_json.object_items()) {
                auto pipeline = pipeline::Make();
                _nato_pipeline[obj.first] = pipeline;
                for (auto &pu : obj.second.array_items()) {
                    std::string id = pu[1].string_value();
                    int turns_until_arrive = pu[3].int_value();
                    if (id.empty())
                        continue;

                    pipeline->add_pipeline_unit(id, turns_until_arrive);
                }
            }
        }

        auto soviet_pipeline_json = data["soviet_pipeline"];
        if (soviet_pipeline_json.is_object()) {
            for (auto &obj : soviet_pipeline_json.object_items()) {
                auto pipeline = pipeline::Make();
                _soviet_pipeline[obj.first] = pipeline;
                for (auto &pu : obj.second.array_items()) {
                    std::string id = pu[1].string_value();
                    int turns_until_arrive = pu[3].int_value();
                    if (id.empty())
                        continue;
                    
                    pipeline->add_pipeline_unit(id, turns_until_arrive);
                }
            }
        }
        
        auto nato_ports_json = data["nato_ports"];
        if (nato_ports_json.is_object()) {
            
            for (auto &obj : nato_ports_json.object_items()) {
                std::string id = obj.first;
                auto fields = obj.second.array_items();
                std::string name = fields[0].string_value();
                int supplies = fields[4].int_value();
                int infantry = fields[5].int_value();
                station_data station(id, name, supplies, infantry);
                _nato_ports[id] = station;
            }
        }
        
        auto soviet_ports_json = data["soviet_ports"];
        if (soviet_ports_json.is_object()) {
            
            for (auto &obj : soviet_ports_json.object_items()) {
                std::string id = obj.first;
                auto fields = obj.second.array_items();
                std::string name = fields[0].string_value();
                int supplies = fields[4].int_value();
                int infantry = fields[5].int_value();
                station_data station(id, name, supplies, infantry);
                _soviet_ports[id] = station;
            }
        }

        auto nato_airbases_json = data["nato_airbases"];
        if (nato_airbases_json.is_object()) {
            
            for (auto &obj : nato_airbases_json.object_items()) {
                std::string id = obj.first;
                auto fields = obj.second.array_items();
                std::string name = fields[0].string_value();
                int supplies = fields[4].int_value();
                int infantry = fields[5].int_value();
                station_data station(id, name, supplies, infantry);
                _nato_airbases[id] = station;
            }
        }

        auto soviet_airbases_json = data["soviet_airbases"];
        if (soviet_airbases_json.is_object()) {
            
            for (auto &obj : soviet_airbases_json.object_items()) {
                std::string id = obj.first;
                auto fields = obj.second.array_items();
                std::string name = fields[0].string_value();
                int supplies = fields[4].int_value();
                int infantry = fields[5].int_value();
                station_data station(id, name, supplies, infantry);
                _soviet_airbases[id] = station;
            }
        }

        auto nato_tfs_json = data["nato_tfs"];
        if (nato_tfs_json.is_object()) {
            for (auto &obj : nato_tfs_json.object_items()) {
                std::string tfid = obj.first;
                auto fields = obj.second.object_items();
                std::string mission_string = fields["mission"].string_value();
                int x = fields["x"].int_value();
                int y = fields["y"].int_value();
                task_force_mission_type mission = task_force_mission_type_utility::to_enum(mission_string);
                auto tf = task_force::Make(tfid, mission, x, y);
                _nato_task_forces[tfid] = tf;
                for (auto &u : fields["units"].array_items()) {
                    std::string id = u[1].string_value();
                    std::shared_ptr<unit> ship_unit = ship_data->find_unit(id);
                    tf->add_unit(ship_unit);
                }
            }
        }

        auto soviet_tfs_json = data["soviet_tfs"];
        if (soviet_tfs_json.is_object()) {
            for (auto &obj : soviet_tfs_json.object_items()) {
                std::string tfid = obj.first;
                auto fields = obj.second.object_items();
                std::string mission_string = fields["mission"].string_value();
                int x = fields["x"].int_value();
                int y = fields["y"].int_value();
                task_force_mission_type mission = task_force_mission_type_utility::to_enum(mission_string);
                auto tf = task_force::Make(tfid, mission, x, y);
                _soviet_task_forces[tfid] = tf;
                for (auto &u : fields["units"].array_items()) {
                    std::string id = u[1].string_value();
                    std::shared_ptr<unit> ship_unit = ship_data->find_unit(id);
                    tf->add_unit(ship_unit);
                }
            }
        }
    }
    
    std::shared_ptr<player> make_player(const affiliation_type affiliation) override
    {
        auto player = player::Make(affiliation);
        
        return player;
    }
    
    const int station_infantry(const std::string &id) override
    {
        if (_nato_ports.find(id) != _nato_ports.end())
            return _nato_ports[id].infantry;

        if (_nato_airbases.find(id) != _nato_airbases.end())
            return _nato_airbases[id].infantry;

        if (_soviet_ports.find(id) != _soviet_ports.end())
            return _soviet_ports[id].infantry;

        if (_soviet_airbases.find(id) != _soviet_airbases.end())
            return _soviet_airbases[id].infantry;
        
        return 0;
    }

    const int station_supplies(const std::string &id) override
    {
        if (_nato_ports.find(id) != _nato_ports.end())
            return _nato_ports[id].supplies;
        
        if (_nato_airbases.find(id) != _nato_airbases.end())
            return _nato_airbases[id].supplies;
        
        if (_soviet_ports.find(id) != _soviet_ports.end())
            return _soviet_ports[id].supplies;
        
        if (_soviet_airbases.find(id) != _soviet_airbases.end())
            return _soviet_airbases[id].supplies;
        
        return 0;
    }
};

const std::string scenario_data::Import_Data(const std::string &path)
{
    // read in scenario data in json
    std::string scenario_data;
    
    auto scenario_file = file::Make(path);
    
    if (scenario_file) {
        if (scenario_file->open(file_mode_open_read)) {
            auto size = scenario_file->size();
            if (size > 0) {
                char *buf = (char *)malloc((size + 1) * sizeof(char));
                buf[size] = '\0';
                
                auto read_bytes = scenario_file->read(buf, size);
                runtime_assert(read_bytes == size);
                
                scenario_data = std::string(buf, size);
                
                scenario_file->close();
                free(buf);
            }
        }
    }
    
    runtime_assert(!scenario_data.empty());
    
    return scenario_data;
}

std::shared_ptr<scenario_data> scenario_data::Make(const std::string &json_import, std::shared_ptr<ShipData> ship_data)
{
    auto scenario = std::make_shared<_scenario_data>();
    scenario->initialize(json_import, ship_data);
    return scenario;
}

std::shared_ptr<player> scenario_data::make_player(const affiliation_type affiliation)
{
    runtime_assert_not_reached();
}

const int scenario_data::station_infantry(const std::string &id)
{
    runtime_assert_not_reached();
}

const int scenario_data::station_supplies(const std::string &id)
{
    runtime_assert_not_reached();
}
