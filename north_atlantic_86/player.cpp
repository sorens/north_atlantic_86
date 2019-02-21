//
//  player.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <uuid/uuid.h>
#include "debug.hpp"
#include "player.hpp"

#pragma mark _Player

class _Player : public Player
{
public:
    _Player(AffiliationType affiliation, const std::string &name) :
    _affiliation(affiliation), _name(name), _score(0)
    {
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_string_t uuid_string;
        uuid_unparse_lower(uuid, uuid_string);
        _id = std::string(uuid_string);
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
        // TODO implement once we expand constructor to inject more data
        return nullptr;
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const std::string name() override
    {
        return _name;
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

std::shared_ptr<Player> Player::factory(const AffiliationType affiliation, const std::string &name)
{
    return std::make_shared<_Player>(affiliation, name);
}

const std::string Player::id()
{
    runtime_assert_not_reached();
}

const std::string Player::name()
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
