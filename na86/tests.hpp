//
//  tests.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/20/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <memory>

class Tests
{
public:

    static std::shared_ptr<Tests> Make();

    virtual void test_all();

    virtual void aircraft_unit_test();
    virtual void game_unit_test();
    virtual void grid_unit_test();
    virtual void map_unit_test();
    virtual void mutable_naval_station_test();
    virtual void mutable_unit_unit_test();
    virtual void naval_station_unit_test();
    virtual void player_unit_test();
    virtual void scenario_data_unit_tests();
    virtual void task_force_unit_test();
    virtual void unit_test();
    virtual void weapon_mount_unit_test();
    virtual void weapon_system_unit_test();
    virtual void weather_unit_test();
};
