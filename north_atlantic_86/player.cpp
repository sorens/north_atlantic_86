//
//  player.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/12/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <uuid/uuid.h>
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
    
private:
    AffiliationType _affiliation;
    std::vector<std::shared_ptr<Fleet>> _fleets;
    std::string _id;
    std::string _name;
    int _score;
    std::vector<std::shared_ptr<Unit>> _sunken_ships;
};

#pragma mark Player

const AffiliationType Player::affiliation()
{
    return AffiliationType::UNKNOWN;
}

const std::string Player::alliance_to_string(const AffiliationType affiliation)
{
    // TODO implement
    return "";
}

// const std::vector<std::shared_ptr<Base>> Player::bases()

std::shared_ptr<Player> Player::factory(const AffiliationType affiliation, const std::string &name)
{
    return std::make_shared<_Player>(affiliation, name);
}

const std::vector<std::shared_ptr<Fleet>> Player::fleets()
{
    return std::vector<std::shared_ptr<Fleet>>(0);
}

const std::string Player::id()
{
    return "";
}

const std::string Player::name()
{
    return "";
}

const int Player::score()
{
    return 0;
}

const std::vector<std::shared_ptr<Unit>> Player::sunken_ships()
{
    return std::vector<std::shared_ptr<Unit>>(0);
}
