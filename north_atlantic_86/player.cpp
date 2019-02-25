//
//  player.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <tuple>
#include <uuid/uuid.h>
#include "debug.hpp"
#include "player.hpp"
#include "player_exception.hpp"

#pragma mark _player

static const int Field_TaskForce_ID         = 0;
static const int Field_TaskForce_AVAILABLE  = 1;

class _player : public player
{
public:
    _player(affilation_type affiliation, const std::string &name, std::vector<std::string> task_force_ids) :
    _affiliation(affiliation), _name(name), _possible_task_forces(task_force_ids.size()), _score(0)
    {
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_string_t uuid_string;
        uuid_unparse_lower(uuid, uuid_string);
        _id = std::string(uuid_string);
        
        // mark all possible task forces as not-used
        for (int i = 0; i < _possible_task_forces.size(); ++i) {
            auto &tf = _possible_task_forces[i];
            std::get<Field_TaskForce_ID>(tf) = task_force_ids[i];
            std::get<Field_TaskForce_AVAILABLE>(tf) = true;
        }
    }
    
    ~_player()
    {
        _possible_task_forces.clear();
    }
    
    const affilation_type affiliation() override
    {
        return _affiliation;
    }
    
    const std::vector<std::shared_ptr<naval_station>> bases() override
    {
        return _bases;
    }
    
    std::shared_ptr<task_force> create_task_force(const task_force_mission_type mission, const int x, const int y) override
    {
        if (number_remaining_task_forces() <= 0)
            throw no_task_forces_available_player_exception();
        
        // find an available TF ID
        std::string id;
        for (auto &tf : _possible_task_forces) {
            if (std::get<Field_TaskForce_AVAILABLE>(tf)) {
                std::get<Field_TaskForce_AVAILABLE>(tf) = false;
                id = std::get<Field_TaskForce_ID>(tf);
                break;
            }
        }
        
        std::shared_ptr<task_force> task_force;
        
        if (!id.empty()) {
            task_force = task_force::Make(id, mission, x, y);
            _task_forces.push_back(task_force);
        }

        return task_force;
    }
    
    void dissolve_task_force(std::shared_ptr<task_force> tf) override
    {
        // TODO throw exception when not in port
        if (tf) {
            // TODO iterate over each unit, put it back in this port
            
            // TODO delete the task force
            
            // TODO update the possible task force array to allow this task force again
        }
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const std::string name() override
    {
        return _name;
    }
    
    const int number_remaining_task_forces() override
    {
        int result = static_cast<int>(_possible_task_forces.size()) - static_cast<int>(_task_forces.size());
        runtime_assert(result >= 0 && result <= _possible_task_forces.size());
        return result;
    }
    
    const int score() override
    {
        return _score;
    }
    
    const std::vector<std::shared_ptr<Unit>> sunken_ships() override
    {
        return _sunken_ships;
    }
    
    const std::vector<std::shared_ptr<task_force>> task_forces() override
    {
        return _task_forces;
    }
    
private:
    affilation_type _affiliation;
    std::vector<std::shared_ptr<naval_station>> _bases;
    std::string _id;
    std::string _name;
    std::vector<std::tuple<std::string, bool>> _possible_task_forces;
    int _score;
    std::vector<std::shared_ptr<Unit>> _sunken_ships;
    std::vector<std::shared_ptr<task_force>> _task_forces;
};

#pragma mark player

const affilation_type player::affiliation()
{
    runtime_assert_not_reached();
}

const std::string player::alliance_to_string(const affilation_type affiliation)
{
    // TODO implement
    return "";
}
    
const std::vector<std::shared_ptr<naval_station>> player::bases()
{
    runtime_assert_not_reached();
}

std::shared_ptr<task_force> player::create_task_force(const task_force_mission_type mission, const int x, const int y)
{
    runtime_assert_not_reached();
}

void player::dissolve_task_force(std::shared_ptr<task_force> tf)
{
    runtime_assert_not_reached();
}

// const std::vector<std::shared_ptr<Base>> player::bases()

const std::string player::id()
{
    runtime_assert_not_reached();
}

std::shared_ptr<player> player::Make(const affilation_type affiliation, const std::string &name, std::vector<std::string> task_force_ids)
{
    return std::make_shared<_player>(affiliation, name, task_force_ids);
}

const std::string player::name()
{
    runtime_assert_not_reached();
}

const int player::number_remaining_task_forces()
{
    runtime_assert_not_reached();
}

const int player::score()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<Unit>> player::sunken_ships()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<task_force>> player::task_forces()
{
    runtime_assert_not_reached();
}
