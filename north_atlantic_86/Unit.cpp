//
//  unit.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "unit.hpp"
#include <sstream>

#pragma mark _Unit

class _Unit : public Unit
{
public:
    _Unit(const std::string &id, const std::string &name, const UnitType type) :
    _id(id), _name(name), _type(type)
    {
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<Unit";
        ss << " id: '" << _id << "'";
        ss << ", name: '" << _name << "'";
        ss << ", type: '" << UnitTypeUtility::to_string(_type) << "'";
        ss << ">";
        
        return ss.str();
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const int max_speed() override
    {
        return _max_speed;
    }
    
    const std::string name() override
    {
        return _name;
    }
    
    const UnitType type() override
    {
        return _type;
    }
    
private:
    std::string _id;
    int _max_speed;
    std::string _name;
    UnitType _type;
};

#pragma mark Unit

const std::string Unit::description()
{
    return "";
}

std::shared_ptr<Unit> Unit::factory(const std::string &id, const std::string &name, const UnitType type)
{
    return std::make_shared<_Unit>(id, name, type);
}

const std::string Unit::id()
{
    return "";
}

const int Unit::max_speed()
{
    return 0;
}

const std::string Unit::name()
{
    return "";
}

const UnitType Unit::type()
{
    return UnitType::Unknown;
}
