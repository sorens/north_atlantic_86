//
//  unit.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/10/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "affiliation_type.hpp"
#include "unit.hpp"
#include <sstream>

#pragma mark _Unit

class _Unit : public Unit {
public:
    _Unit(const std::string &id, const std::string &name, const UnitType type)
    : _id(id), _name(name), _type(type)
    {
    }
    
    _Unit(const std::string &id, const std::string &name, const UnitType type,
          const std::string &unit_class, const int class_id, const int main_gun, const int aa_gun, const int missile_defense, const int max_speed, const int cargo_capacity, const int defense_factor, const AffiliationType affiliation)
    : _anti_aircraft_gun(aa_gun), _cargo_capacity(cargo_capacity), _defense_factor(defense_factor), _id(id), _main_gun(main_gun), _max_speed(max_speed), _missile_defense(missile_defense), _name(name), _type(type), _unit_class(unit_class), _affiliation(affiliation)
    {
    }
    
    const int anti_aircraft_gun() override
    {
        return _anti_aircraft_gun;
    }
    
    const int cargo_capacity() override
    {
        return _cargo_capacity;
    }
    
    const int defense_factor() override
    {
        return _defense_factor;
    }
    
    const std::string description() override
    {
        std::stringstream ss;
        ss << "<Unit";
        ss << " id: '" << _id << "'";
        ss << ", class: '" << _unit_class << "'";
        ss << ", name: '" << _name << "'";
        ss << ", type: '" << UnitTypeUtility::to_string(_type) << "'";
        ss << ", main_gun: " << _main_gun;
        ss << ", aa_gun: " << _anti_aircraft_gun;
        ss << ", missile_defense: " << _missile_defense;
        ss << ", max_speed: " << _max_speed;
        ss << ", defense_factor: " << _defense_factor;
        ss << ", cargo_capacity: " << _cargo_capacity;
        ss << ">";
        
        return ss.str();
    }
    
    const std::string id() override
    {
        return _id;
    }
    
    const int main_gun() override
    {
        return _main_gun;
    }
    
    const int max_speed() override
    {
        return _max_speed;
    }
    
    const int missile_defense() override
    {
        return _missile_defense;
    }
    
    const std::string name() override
    {
        return _name;
    }
    
    const UnitType type() override
    {
        return _type;
    }
    
    const std::string unit_class() override
    {
        return _unit_class;
    }
    
private:
    AffiliationType _affiliation;
    int _anti_aircraft_gun;
    int _cargo_capacity;
    int _defense_factor;
    std::string _id;
    int _main_gun;
    int _max_speed;
    int _missile_defense;
    std::string _name;
    UnitType _type;
    std::string _unit_class;
    int _class_id;
};

#pragma mark Unit

const int Unit::anti_aircraft_gun()
{
    return 0;
}

const int Unit::cargo_capacity()
{
    return 0;
}

const int Unit::defense_factor()
{
    return 0;
}

const std::string Unit::description()
{
    return "";
}

std::shared_ptr<Unit> Unit::factory(const std::string &id, const std::string &name, const UnitType type)
{
    return std::make_shared<_Unit>(id, name, type);
}

std::shared_ptr<Unit> Unit::factory(const std::string &id, const std::string &name, const UnitType type, const std::string &unit_class, const int class_id, const int main_gun, const int aa_gun, const int missile_defense, const int max_speed, const int cargo_capacity, const int defense_factor, const AffiliationType affiliation)
{
    return std::make_shared<_Unit>(id, name, type, unit_class, class_id, main_gun, aa_gun, missile_defense, max_speed, cargo_capacity, defense_factor, affiliation);
}

const std::string Unit::id()
{
    return "";
}

const int Unit::main_gun()
{
    return 0;
}

const int Unit::max_speed()
{
    return 0;
}

const int Unit::missile_defense()
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

const std::string Unit::unit_class()
{
    return "";
}
