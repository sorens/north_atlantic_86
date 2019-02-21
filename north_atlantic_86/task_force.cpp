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

#pragma mark _TaskForce

class _TaskForce : public TaskForce
{
public:
    _TaskForce(const std::string id, const TaskForceMissionType mission, const int x, const int y) :
    _id(id), _mission(mission), _x(x), _y(y)
    {
    }
    
    void add_unit(std::shared_ptr<Unit> unit) override
    {
        if (!unit)
            return;
        
        std::string prefix = unit->prefix();
        
        if (prefix[0] == 'C' && prefix[1] == 'V') {
            if (_mission != TaskForceMissionType::COMBAT) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in COMBAT missions");
            }
        }
        else if (prefix[0] == 'S') {
            if (_mission != TaskForceMissionType::SUBMARINE) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in SUBMARINE missions");
            }
        }
        else if (prefix[0] == 'L') {
            if (_mission != TaskForceMissionType::TRANSPORT && _mission != TaskForceMissionType::EVACUATION) {
                throw ship_not_allowed_for_mission_task_force_exception(prefix + " only allowed in TRANSPORT or EVACUATION missions");
            }
        }
        else if (prefix[0] == 'A') {
            if (_mission != TaskForceMissionType::TRANSPORT) {
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
    
    const TaskForceMissionType mission() override
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
    
    void set_mission_type(const TaskForceMissionType mission) override
    {
        _mission = mission;
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
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<Task Force";
        ss << " id: " << _id;
        ss << " mission: " << TaskForceMissionTypeUtility::To_String(_mission);
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
    TaskForceMissionType _mission;
    std::vector<std::weak_ptr<Unit>> _units;
    int _x;
    int _y;
};

#pragma mark TaskForce

void TaskForce::add_unit(std::shared_ptr<Unit> unit)
{
    runtime_assert_not_reached();
}

const std::string TaskForce::description()
{
    runtime_assert_not_reached();
}

const std::string TaskForce::id()
{
    runtime_assert_not_reached();
}

std::shared_ptr<TaskForce> TaskForce::Make(const std::string &id, const TaskForceMissionType mission, const int x, const int y)
{
    return std::make_shared<_TaskForce>(id, mission, x, y);
}

const int TaskForce::max_speed()
{
    runtime_assert_not_reached();
}

const TaskForceMissionType TaskForce::mission()
{
    runtime_assert_not_reached();
}

void TaskForce::remove_unit(const std::string &id)
{
    runtime_assert_not_reached();
}

void TaskForce::set_mission_type(const TaskForceMissionType mission)
{
    runtime_assert_not_reached();
}

const std::vector<std::weak_ptr<Unit>> TaskForce::units()
{
    runtime_assert_not_reached();
}

const int TaskForce::x()
{
    runtime_assert_not_reached();
}

const int TaskForce::y()
{
    runtime_assert_not_reached();
}
