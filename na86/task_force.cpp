//
//  task_force.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "debug.hpp"
#include "task_force.hpp"
#include "task_force_exception.hpp"

#pragma mark _task_force

class _task_force : public task_force
{
public:
    _task_force(const std::string id, const task_force_mission_type mission, const int x, const int y) :
    _id(id), _mission(mission), _x(x), _y(y)
    {
    }
    
    void add_unit(std::shared_ptr<unit> unit) override
    {
        if (!unit)
            return;
        
        std::string prefix = unit->prefix();
        
        if (prefix[0] == 'C' && prefix[1] == 'V') {
            if (_mission != task_force_mission_type::COMBAT) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in COMBAT missions");
            }
        }
        else if (prefix[0] == 'S') {
            if (_mission != task_force_mission_type::SUBMARINE) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in SUBMARINE missions");
            }
        }
        else if (prefix[0] == 'L') {
            if (_mission != task_force_mission_type::TRANSPORT && _mission != task_force_mission_type::EVACUATION) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in TRANSPORT or EVACUATION missions");
            }
        }
        else if (prefix[0] == 'A') {
            if (_mission != task_force_mission_type::TRANSPORT) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in TRANSPORT missions");
            }
        }
        
        logverbose("task force '" << _id << "' adding unit: " << unit->description());
        _units.push_back(unit);
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const task_force_mission_type mission() override
    {
        return _mission;
    }
    
    const int max_speed() override
    {
        int max_speed = 30;         // 30
        
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
    
    void set_mission_type(const task_force_mission_type mission) override
    {
        _mission = mission;
    }
    
    const std::vector<std::weak_ptr<unit>> units() override
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
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<task force";
        ss << " id: " << _id;
        ss << " mission: " << task_force_mission_type_utility::to_string(_mission);
        ss << " location: " << _x << ", " << _y;
        ss << " units (" << _units.size() << "): ";
        for (auto &unit : _units) {
            if (auto strong = unit.lock())
                ss << strong->id() << ", ";
        }
        ss << ">";
        
        return ss.str();
    }
    
private:
    std::string _id;
    task_force_mission_type _mission;
    std::vector<std::weak_ptr<unit>> _units;
    int _x;
    int _y;
};

#pragma mark task_force

void task_force::add_unit(std::shared_ptr<unit> unit)
{
    runtime_assert_not_reached();
}

const std::string task_force::description()
{
    runtime_assert_not_reached();
}

const std::string task_force::id()
{
    runtime_assert_not_reached();
}

std::shared_ptr<task_force> task_force::Make(const std::string &id, const task_force_mission_type mission, const int x, const int y)
{
    return std::make_shared<_task_force>(id, mission, x, y);
}

const int task_force::max_speed()
{
    runtime_assert_not_reached();
}

const task_force_mission_type task_force::mission()
{
    runtime_assert_not_reached();
}

void task_force::remove_unit(const std::string &id)
{
    runtime_assert_not_reached();
}

void task_force::set_mission_type(const task_force_mission_type mission)
{
    runtime_assert_not_reached();
}

const std::vector<std::weak_ptr<unit>> task_force::units()
{
    runtime_assert_not_reached();
}

const int task_force::x()
{
    runtime_assert_not_reached();
}

const int task_force::y()
{
    runtime_assert_not_reached();
}
