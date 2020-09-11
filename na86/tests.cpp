//
//  tests.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include "aircraft_data.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "game.hpp"
#include "log.hpp"
#include "map.hpp"
#include "map_data.hpp"
#include "mutable_unit.hpp"
#include "naval_station_data.hpp"
#include "naval_station_data_exception.hpp"
#include "player.hpp"
#include "player_exception.hpp"
#include "scenario_data.hpp"
#include "ship_data.hpp"
#include "task_force.hpp"
#include "task_force_exception.hpp"
#include "tests.hpp"
#include "weapon_data.hpp"
#include "weapon_mount.hpp"
#include "weapon_mount_exception.hpp"

#pragma mark _Tests

class _Tests : public Tests
{
public:
    _Tests()
    {
        _initialize_once();
    }
    
    ~_Tests()
    {
        _clean_up_once();
    }
    
    void _initialize_once()
    {
    }

    void _initialize_every_time()
    {
        Log::change_log_level(LogLevel::VERBOSE);

        // read in map data
        std::string map_data = map_data::Import_Data("map_data.json");
        
        // read in ship_data.json
        std::string ship_data = ship_data::Import_Data("ship_data.json");
       
        // read in scenario data
        std::string scenario_data = scenario_data::Import_Data("scenario_1_data.json");

        // read in weapon_data.json
        std::string weapon_data = weapon_data::Import_Data("weapon_data.json");
        
        // read in aircraft_data.json
        std::string aircraft_data = aircraft_data::Import_Data("aircraft_data.json");
        
        // read in naval_station_data.json
        std::string naval_station_data = naval_station_data::Import_Data("naval_station_data.json");

        _game = game::Make(map_data, ship_data, weapon_data, aircraft_data, naval_station_data, scenario_data);
        _game->add_nato_player("Sally");
        _game->add_soviet_player("Yuri");    
    }

    void _clean_up_every_time()
    {
        _game = nullptr;
    }

    void _clean_up_once()
    {
    }
    
    void test_result(const std::string &test_case, const std::string &message, const bool result)
    {
        std::string result_string = "🛑,";
        if (result)
            result_string = "🟢,";
        
        std::string test_case_with_markers = "'" + test_case + "'";
        std::string message_with_markers = "'" + message + "'";
        
        std::cout << "<TEST CASE result: " << std::left << std::setw(8) << result_string << std::left << std::setw(30) << test_case_with_markers << "CONDITION: " << std::left << std::setw(60) << message_with_markers << ">" << std::endl;
    }
    
    void test_all() override
    {
        loginfo("** all tests: BEGIN");
        aircraft_unit_test();
        grid_unit_test();
        map_unit_test();
        mutable_unit_unit_test();
        naval_station_unit_test();
        player_unit_test();
        scenario_data_unit_tests();
        task_force_unit_test();
        unit_test();
        weapon_mount_unit_test();
        weapon_system_unit_test();
        weather_unit_test();
        loginfo("** all tests: FINISHED");
    }
    
    void aircraft_unit_test() override
    {
        _initialize_every_time();
        
        auto f14 = _game->aircraft("F14");
        bool result = false;
        if (f14)
            result = true;
        
        test_result("aircraft_unit_test", "Lookup F14", result);
        
        result = false;
        auto phoenix = f14->aaw_weapon_system();
        if (phoenix && phoenix->name() == "Phoenix")
            result = true;
        
        test_result("aircraft_unit_test", "F14 has a Phoenix weapons system", result);
        
        _clean_up_every_time();
    }

    void grid_unit_test() override
    {
        _initialize_every_time();
        
        auto wd = weapon_data::Make(weapon_data::Import_Data("weapon_data.json"));
        auto ship_data = ship_data::factory(ship_data::Import_Data("ship_data.json"));
        auto sd = scenario_data::Make(scenario_data::Import_Data("scenario_1_data.json"), ship_data);
        auto naval_station_data = naval_station_data::Make(naval_station_data::Import_Data("naval_station_data.json"), wd, sd);
        
        bool result = false;
        auto grid1 = grid::Make("A", grid_type::Ocean, 4, 5, naval_station_data);
        auto grid2 = grid::Make("b", grid_type::Ocean, 9, 6, naval_station_data);
        float distance = grid::Distance(grid1, grid2);
        if (distance == 6)
            result = true;
        test_result("grid_unit_test", "Calculate distance between grids", result);
        
        _clean_up_every_time();
    }

    void map_unit_test() override
    {
        _initialize_every_time();
        _clean_up_every_time();
    }

    void mutable_unit_unit_test() override
    {
        _initialize_every_time();
        _clean_up_every_time();
    }
    
    void naval_station_unit_test() override
    {
        _initialize_every_time();

        test_result("naval_station_unit_test", "Found America", _game->find_naval_station("America") != nullptr);
        test_result("naval_station_unit_test", "Found Murmansk", _game->find_naval_station("Murmansk") != nullptr);
        test_result("naval_station_unit_test", "Found Riga", _game->find_naval_station("Riga") != nullptr);
        test_result("naval_station_unit_test", "Found Bergen", _game->find_naval_station("Bergen") != nullptr);
        test_result("naval_station_unit_test", "Found Hamburg", _game->find_naval_station("Hamburg") != nullptr);
        test_result("naval_station_unit_test", "Found Scapa Flow", _game->find_naval_station("Scapa Flow") != nullptr);
        test_result("naval_station_unit_test", "Found NATO Faroes", _game->find_naval_station("faroes-nato") != nullptr);
        test_result("naval_station_unit_test", "Found NATO Iceland", _game->find_naval_station("Iceland-nato") != nullptr);
        test_result("naval_station_unit_test", "Found SOVIET Faroes", _game->find_naval_station("Faroes-SOVIET") != nullptr);
        test_result("naval_station_unit_test", "Found SOVIET Iceland", _game->find_naval_station("Iceland-soviet") != nullptr);
        test_result("naval_station_unit_test", "Won't find Chicago", _game->find_naval_station("Chicago") == nullptr);
        
        test_result("naval_station_unit_test", "Iceland-NATO is NATO", _game->find_naval_station("Iceland-NATO")->affiliation() == affiliation_type::NATO);
        test_result("naval_station_unit_test", "Iceland-NATO is an AIRBASE", _game->find_naval_station("Iceland-NATO")->type() == naval_station_type::Airbase);
        test_result("naval_station_unit_test", "Iceland-NATO has 30 light guns", _game->find_naval_station("Iceland-NATO")->anti_aircraft_gun() == 30);
        test_result("naval_station_unit_test", "Iceland-NATO has 0 missile defense", _game->find_naval_station("Iceland-NATO")->missible_defense() == 0);
        test_result("naval_station_unit_test", "Iceland-NATO has 80 aircraft capacity", _game->find_naval_station("Iceland-NATO")->airbase_capacity() == 80);
        test_result("naval_station_unit_test", "Iceland-NATO has 99 defense factor", _game->find_naval_station("Iceland-NATO")->defense_factor() == 99);
        test_result("naval_station_unit_test", "Iceland-NATO has 12 helicopters", _game->find_naval_station("Iceland-NATO")->helicopters() == 12);
        test_result("naval_station_unit_test", "Iceland-NATO has 4 EW strength", _game->find_naval_station("Iceland-NATO")->ew_strength() == 4);
        test_result("naval_station_unit_test", "Iceland-NATO has 0 SONAR strength", _game->find_naval_station("Iceland-NATO")->sonar_strength() == 0);
        test_result("naval_station_unit_test", "Iceland-NATO has 120 infantry", _game->find_naval_station("Iceland-NATO")->infantry_remaining() == 120);
        test_result("naval_station_unit_test", "Iceland-NATO has 20 supplies", _game->find_naval_station("Iceland-NATO")->supplies_remaining() == 20);
        
        test_result("naval_station_unit_test", "Murmansk is SOVIET", _game->find_naval_station("Murmansk")->affiliation() == affiliation_type::SOVIET);
        test_result("naval_station_unit_test", "Murmansk is a PORT", _game->find_naval_station("Murmansk")->type() == naval_station_type::Port);
        
        _clean_up_every_time();
    }

    void player_unit_test() override
    {
        _initialize_every_time();
        
        auto nato = _game->player_nato();
        
        bool result = true;
        for (int i = 1; i < 14; ++i) {
            try {
                auto tf = nato->create_task_force(task_force_mission_type::COMBAT, 10, 10);
                if (tf && i > 11)
                    result = false;
            }
            catch(no_task_forces_available_player_exception &e) {
                if (nato->task_forces().size() < 11)
                    result = false;
            }
        }
        
        test_result("player_unit_test", "nato player can only have 11 task forces", result);
        
        auto soviet = _game->player_soviet();
        result = true;
        for (int i = 1; i < 14; ++i) {
            try {
                auto tf = soviet->create_task_force(task_force_mission_type::COMBAT, 10, 10);
                if (tf && i > 9)
                    result = false;
            }
            catch(no_task_forces_available_player_exception &e) {
                if (soviet->task_forces().size() < 9)
                    result = false;
            }
        }
        
        test_result("player_unit_test", "soviet player can only have 9 task forces", result);
        
        _clean_up_every_time();
    }
    
    void scenario_data_unit_tests() override
    {
        _initialize_every_time();
        
        auto sd = _game->scenario();
        test_result("scenario_data_unit_test", "initialize scenario 1 data", sd != nullptr);
        
        int supplies = sd->station_supplies("AMERICA");
        test_result("scenario_data_unit_test", "there are 900 supplies in America", supplies == 900);
        
        _clean_up_every_time();
    }

    void task_force_unit_test() override
    {
        _initialize_every_time();

        // TRANSPORT Task Force
        auto transport_tf = task_force::Make("11", task_force_mission_type::TRANSPORT, 1, 1);
        auto nimitz = _game->ship_unit("CVN-68");
        
        bool result = false;
        try
        {
            transport_tf->add_unit(nimitz);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_forces_unit_test", "Prevent CVN adding to Transport TF", result);
        
        auto kennedy = _game->ship_unit("CV-67");
        
        result = false;
        try
        {
            transport_tf->add_unit(kennedy);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent CV adding to Transport TF", result);

        auto philadelphia = _game->ship_unit("SSN-690");

        result = false;
        try
        {
            transport_tf->add_unit(philadelphia);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent SSN adding to Transport TF", result);

        
        // COMBAT Task Force
        auto combat_tf = task_force::Make("12", task_force_mission_type::COMBAT, 1, 1);
        
        auto guam = _game->ship_unit("LPH-9");
        
        result = false;
        try
        {
            combat_tf->add_unit(guam);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent LPH adding to Combat TF", result);

        auto comet = _game->ship_unit("AKR-7");
        
        result = false;
        try
        {
            combat_tf->add_unit(comet);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent AKR adding to Combat TF", result);
        
        result = false;
        try
        {
            combat_tf->add_unit(philadelphia);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent SSN adding to Combat TF", result);

        // BOMBARDMENT Task Force
        auto bombardment_tf = task_force::Make("13", task_force_mission_type::BOMBARDMENT, 1, 1);

        result = false;
        try
        {
            bombardment_tf->add_unit(nimitz);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent CVN adding to Bombardment TF", result);

        result = false;
        try
        {
            bombardment_tf->add_unit(kennedy);
        }
        catch (ship_not_allowed_for_mission_task_force_exception &e)
        {
            result = true;
        }
        
        test_result("task_force_unit_test", "Prevent CV adding to Bombardment TF", result);

        // EVACUATION Task Force
        auto evacuation_tf = task_force::Make("13", task_force_mission_type::EVACUATION, 1, 1);
        
        _clean_up_every_time();
    }

    void unit_test() override
    {
        _initialize_every_time();

        auto nimitz_mutable = mutable_unit::Make(_game->ship_unit("CVN-68"));
        nimitz_mutable->apply_damage(nimitz_mutable->immutable_unit()->defense_factor() + 1);
        
        bool result = false;
        if (nimitz_mutable->is_sunk())
            result = true;
        
        test_result("unit_test", "Ship sinks when dmg >= df", result);
        
        result = false;
        nimitz_mutable = mutable_unit::Make(_game->ship_unit("CVN-68"));
        nimitz_mutable->apply_damage(nimitz_mutable->immutable_unit()->defense_factor() / 2);
        if (!nimitz_mutable->is_sunk())
            result = true;

        test_result("unit_test", "Ship does not sink when dmg < df", result);

        _clean_up_every_time();
    }

    void weapon_mount_unit_test() override
    {
        _initialize_every_time();

        bool result = false;
        auto harpoon = _game->find_weapon_system("HARPOON");
        if (harpoon) {
            auto wm = weapon_mount::Make(harpoon, 100, 10);
            
            try {
                while (wm->rounds_remaining() > 0) {
                    wm->fire(9);
                }
            }
            catch(not_enough_rounds_weapon_mount_exception &e) {
                result = true;
            }
        }
        
        test_result("weapon_mount_unit_test", "Exception received when weapon fired with empty magazine", result);
        
        _clean_up_every_time();
    }

    void weapon_system_unit_test() override
    {

    }

    void weather_unit_test() override
    {

    }

private:
    std::shared_ptr<game> _game;
};

#pragma mark Tests

std::shared_ptr<Tests> Tests::Make()
{
    return std::make_shared<_Tests>();
}

void Tests::test_all()
{
    runtime_assert_not_reached();
}

void Tests::aircraft_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::grid_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::map_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::mutable_unit_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::naval_station_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::player_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::scenario_data_unit_tests()
{
    runtime_assert_not_reached();
}

void Tests::task_force_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::unit_test()
{
    runtime_assert_not_reached();
}

void Tests::weapon_mount_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::weapon_system_unit_test()
{
    runtime_assert_not_reached();
}

void Tests::weather_unit_test()
{
    runtime_assert_not_reached();
}
