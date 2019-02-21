//
//  tests.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include "debug.hpp"
#include "file.hpp"
#include "game.hpp"
#include "map.hpp"
#include "mutable_unit.hpp"
#include "player.hpp"
#include "player_exception.hpp"
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
        // read in map data
        std::string map_data = MapSetup::Import_Data("map_data.json");
        
        // read in ship_data.json
        std::string ship_data = ShipData::Import_Data("ship_data.json");
       
        // read in weapon_data.json
        std::string weapon_data = WeaponData::Import_Data("weapon_data.json");

        auto setup_data = MapSetup::factory(map_data);
        _game = Game::Make(setup_data, ship_data, weapon_data);
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
        std::string result_string = "💥,";
        if (result)
            result_string = "✅,";
        
        std::string test_case_with_markers = "'" + test_case + "', ";
        std::string message_with_markers = "'" + message + "', ";
        
        std::cout << "<TEST CASE result: " << std::left << std::setw(6) << result_string << std::left << std::setw(30) << test_case_with_markers << "CONDITION: " << std::left << std::setw(40) << message_with_markers << std::endl;
    }
    
    void test_all() override
    {
        grid_unit_test();
        map_unit_test();
        mutable_unit_unit_test();
        player_unit_test();
        task_force_unit_test();
        unit_test();
        weapon_mount_unit_test();
        weapon_system_unit_test();
        weather_unit_test();
    }

    void grid_unit_test() override
    {

    }

    void map_unit_test() override
    {

    }

    void mutable_unit_unit_test() override
    {

    }

    void player_unit_test() override
    {
        _initialize_every_time();
        
        auto nato = _game->player_nato();
        
        bool result = true;
        for (int i = 1; i < 14; ++i) {
            try {
                auto tf = nato->create_task_force(TaskForceMissionType::COMBAT, 10, 10);
                if (tf && i > 11)
                    result = false;
            }
            catch(no_task_forces_available_player_exception &e) {
                if (i < 12)
                    result = false;
            }
        }
        
        test_result("player_unit_test", "nato player can only have 11 task forces", result);
        
        auto soviet = _game->player_soviet();
        result = true;
        for (int i = 1; i < 14; ++i) {
            try {
                auto tf = soviet->create_task_force(TaskForceMissionType::COMBAT, 10, 10);
                if (tf && i > 9)
                    result = false;
            }
            catch(no_task_forces_available_player_exception &e) {
                if (i < 10)
                    result = false;
            }
        }
        
        test_result("player_unit_test", "soviet player can only have 9 task forces", result);
        
        _clean_up_every_time();
    }

    void task_force_unit_test() override
    {
        _initialize_every_time();

        // TRANSPORT Task Force
        auto transport_tf = TaskForce::Make("11", TaskForceMissionType::TRANSPORT, 1, 1);
        auto nimitz = _game->unit("CVN-68");
        
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
        
        auto kennedy = _game->unit("CV-67");
        
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

        auto philadelphia = _game->unit("SSN-690");

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
        auto combat_tf = TaskForce::Make("12", TaskForceMissionType::COMBAT, 1, 1);
        
        auto guam = _game->unit("LPH-9");
        
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

        auto comet = _game->unit("AKR-7");
        
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
        auto bombardment_tf = TaskForce::Make("13", TaskForceMissionType::BOMBARDMENT, 1, 1);

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
        auto evacuation_tf = TaskForce::Make("13", TaskForceMissionType::EVACUATION, 1, 1);
        
        _clean_up_every_time();
    }

    void unit_test() override
    {
        _initialize_every_time();

        auto nimitz_mutable = MutableUnit::factory(_game->unit("CVN-68"));
        nimitz_mutable->apply_damage(nimitz_mutable->unit()->defense_factor() + 1);
        
        bool result = false;
        if (nimitz_mutable->is_sunk())
            result = true;
        
        test_result("unit_test", "Ship sinks when dmg >= df", result);
        
        result = false;
        nimitz_mutable = MutableUnit::factory(_game->unit("CVN-68"));
        nimitz_mutable->apply_damage(nimitz_mutable->unit()->defense_factor() / 2);
        if (!nimitz_mutable->is_sunk())
            result = true;

        test_result("unit_test", "Ship does not sink when dmg < df", result);

        _clean_up_every_time();
    }

    void weapon_mount_unit_test() override
    {
        _initialize_every_time();

        bool result = false;
        auto harpoon = _game->weapon_system("HARPOON");
        if (harpoon) {
            auto wm = WeaponMount::Make(harpoon, 100, 10);
            
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
    std::shared_ptr<Game> _game;
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

void Tests::player_unit_test()
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
