//
//  naval_station.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "naval_station.hpp"
#include "naval_station_type.hpp"
#include "debug.hpp"

#pragma mark _naval_station

class _naval_station : public naval_station
{
    AffiliationType _affiliation;
    int _airbase_capacity;
    int _anti_aircraft_gun;
    int _defense_factor;
    int _ew_strength;
    int _helicopters;
    int _main_guns;
    int _missile_defense;
    std::string _name;
    int _sonar_strength;
    naval_station_type _type;
    std::shared_ptr<WeaponSystem> _ssm;
    int _ssm_salvo_rate;
    int _ssm_magazine_capacity;
    std::shared_ptr<WeaponSystem> _asw;
    std::shared_ptr<WeaponSystem> _sam;
    std::shared_ptr<WeaponSystem> _ast;

public:
    _naval_station(const std::string &name,
                   const AffiliationType affiliation,
                   const naval_station_type type,
                   const int airbase_capacity,
                   const int aa,
                   const int df,
                   const int ew,
                   const int helicopters,
                   const int mg,
                   const int md,
                   const int sonar,
                   std::shared_ptr<WeaponSystem> ssm,
                   const int ssm_salvo_rate,
                   const int ssm_magazine_capacity,
                   std::shared_ptr<WeaponSystem> asw,
                   std::shared_ptr<WeaponSystem> sam,
                   std::shared_ptr<WeaponSystem> ast) :
    _affiliation(affiliation), _airbase_capacity(airbase_capacity), _anti_aircraft_gun(aa), _defense_factor(df), _ew_strength(ew), _helicopters(helicopters), _main_guns(mg), _missile_defense(md), _name(name), _sonar_strength(sonar), _type(type), _ssm(ssm), _ssm_salvo_rate(ssm_salvo_rate), _ssm_magazine_capacity(ssm_magazine_capacity), _asw(asw), _sam(sam), _ast(ast)
    {
    }

    const AffiliationType affiliation() override
    {
        return _affiliation;
    }

    const int airbase_capacity() override
    {
        return _airbase_capacity;
    }

    const int anti_aircraft_gun() override
    {
        return _anti_aircraft_gun;
    }

    const int defense_factor() override
    {
        return _defense_factor;
    }

    const int ew_strength() override
    {
        return _ew_strength;
    }

    const int helicopters() override
    {
        return _helicopters;
    }

    const int main_guns() override
    {
        return _main_guns;
    }
    
    const int missible_defense() override
    {
        return _missile_defense;
    }

    const std::string name() override
    {
        return _name;
    }

    const int sonar_strength() override
    {
        return _sonar_strength;
    }

    const naval_station_type type() override
    {
        return _type;
    }

    std::shared_ptr<WeaponSystem> weapon_system(const WeaponSystemType t) override
    {
        if (WeaponSystemType::SSM == t) {
            return _ssm;
        }
        else if (WeaponSystemType::ASW == t) {
            return _asw;
        }
        else if (WeaponSystemType::SAM == t) {
            return _sam;
        }
        else if (WeaponSystemType::AST == t) {
            return _ast;
        }

        return nullptr;
    }
};

#pragma mark naval_station

const AffiliationType naval_station::affiliation()
{
    runtime_assert_not_reached();
}

const int naval_station::airbase_capacity()
{
    runtime_assert_not_reached();
}

const int naval_station::anti_aircraft_gun()
{
    runtime_assert_not_reached();
}

const int naval_station::defense_factor()
{
    runtime_assert_not_reached();
}

const int naval_station::ew_strength()
{
    runtime_assert_not_reached();
}

const int naval_station::helicopters()
{
    runtime_assert_not_reached();
}

const int naval_station::main_guns()
{
    runtime_assert_not_reached();
}

std::shared_ptr<naval_station> naval_station::Make(const std::string &name,
                                                   const AffiliationType affiliation,
                                                   const naval_station_type type,
                                                   const int airbase_capacity,
                                                   const int aa,
                                                   const int df,
                                                   const int ew,
                                                   const int helicopters,
                                                   const int mg,
                                                   const int md,
                                                   const int sonar,
                                                   std::shared_ptr<WeaponSystem> ssm,
                                                   const int ssm_salvo_rate,
                                                   const int ssm_magazine_capacity,
                                                   std::shared_ptr<WeaponSystem> asw,
                                                   std::shared_ptr<WeaponSystem> sam,
                                                   std::shared_ptr<WeaponSystem> ast)
{
    return std::make_shared<_naval_station>(name, affiliation, type, airbase_capacity,
                                            aa, df, ew, helicopters, mg, md, sonar, ssm,
                                            ssm_salvo_rate, ssm_magazine_capacity, asw,
                                            sam, ast);
}

const std::string naval_station::name()
{
    runtime_assert_not_reached();
}

const int naval_station::missible_defense()
{
    runtime_assert_not_reached();
}

const int naval_station::sonar_strength()
{
    runtime_assert_not_reached();
}

const naval_station_type naval_station::type()
{
    runtime_assert_not_reached();
}

std::shared_ptr<WeaponSystem> naval_station::weapon_system(const WeaponSystemType t)
{
    runtime_assert_not_reached();
}
