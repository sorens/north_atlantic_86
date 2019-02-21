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

#pragma mark _Player

static const int Field_TaskForce_ID         = 0;
static const int Field_TaskForce_AVAILABLE  = 1;

class _Player : public Player
{
public:
    _Player(AffiliationType affiliation, const std::string &name, std::vector<std::string> task_force_ids) :
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
    
    ~_Player()
    {
        _possible_task_forces.clear();
    }
    
    const AffiliationType affiliation() override
    {
        return _affiliation;
    }
    
    void add_task_force(std::shared_ptr<TaskForce> task_force) override
    {
        
    }
    
    std::shared_ptr<TaskForce> create_task_force(const TaskForceMissionType mission, const int x, const int y) override
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
        
        std::shared_ptr<TaskForce> task_force;
        
        if (!id.empty()) {
            task_force = TaskForce::Make(id, mission, x, y);
            _task_forces.push_back(task_force);
        }

        return task_force;
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
    
    const std::vector<std::shared_ptr<TaskForce>> task_forces() override
    {
        return _task_forces;
    }
    
private:
    AffiliationType _affiliation;
    std::string _id;
    std::string _name;
    std::vector<std::tuple<std::string, bool>> _possible_task_forces;
    int _score;
    std::vector<std::shared_ptr<Unit>> _sunken_ships;
    std::vector<std::shared_ptr<TaskForce>> _task_forces;
};

#pragma mark Player

const AffiliationType Player::affiliation()
{
    runtime_assert_not_reached();
}

void Player::add_task_force(std::shared_ptr<TaskForce> task_force)
{
    runtime_assert_not_reached();
}

const std::string Player::alliance_to_string(const AffiliationType affiliation)
{
    // TODO implement
    return "";
}

std::shared_ptr<TaskForce> Player::create_task_force(const TaskForceMissionType mission, const int x, const int y)
{
    runtime_assert_not_reached();
}

// const std::vector<std::shared_ptr<Base>> Player::bases()

const std::string Player::id()
{
    runtime_assert_not_reached();
}

std::shared_ptr<Player> Player::Make(const AffiliationType affiliation, const std::string &name, std::vector<std::string> task_force_ids)
{
    return std::make_shared<_Player>(affiliation, name, task_force_ids);
}

const std::string Player::name()
{
    runtime_assert_not_reached();
}

const int Player::number_remaining_task_forces()
{
    runtime_assert_not_reached();
}

const int Player::score()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<Unit>> Player::sunken_ships()
{
    runtime_assert_not_reached();
}

const std::vector<std::shared_ptr<TaskForce>> Player::task_forces()
{
    runtime_assert_not_reached();
}
