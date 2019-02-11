//
//  fleet.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "fleet.hpp"

#pragma mark _Fleet

class _Fleet : public Fleet
{
public:
    _Fleet(const std::string id, const int x, const int y) :
    _id(id), _x(x), _y(y)
    {
    }
    
    void add_unit(std::shared_ptr<Unit> unit) override
    {
        if (unit)
            _units.push_back(unit);
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const int max_speed() override
    {
        int max_speed = INT_MAX;
        
        for (auto u : _units) {
            if (auto strong = u.lock()) {
                max_speed = std::min(max_speed, strong->max_speed());
            }
        }
        
        return max_speed;
    }
    
    void remove_unit(const std::string &id) override
    {
        for (auto iter = _units.begin(); iter != _units.end(); ++iter) {
            auto weak = *iter;
            if (auto strong = weak.lock()) {
                if (strong->id() == id) {
                    _units.erase(iter);
                    break;
                }
            }
        }
    }
    
    const std::vector<std::weak_ptr<Unit>> units() override
    {
        return _units;
    }
    
    const int x() override
    {
        return _x;
    }
    
    const int y() override
    {
        return _y;
    }
    
private:
    std::string _id;
    std::vector<std::weak_ptr<Unit>> _units;
    int _x;
    int _y;
};

#pragma mark Fleet

void Fleet::add_unit(std::shared_ptr<Unit> unit)
{
}

std::shared_ptr<Fleet> Fleet::factory(const std::string &id, const int x, const int y)
{
    return std::make_shared<_Fleet>(id, x, y);
}

const std::string Fleet::id()
{
    return "";
}

void Fleet::remove_unit(const std::string &id)
{
}

const int Fleet::max_speed()
{
    return 0;
}

const std::vector<std::weak_ptr<Unit>> Fleet::units()
{
    return std::vector<std::weak_ptr<Unit>>(0);
}

const int Fleet::x()
{
    return -1;
}

const int Fleet::y()
{
    return -1;
}
