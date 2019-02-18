//
//  weapon_data.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/17/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include <unordered_map>
#include "weapon_data.hpp"
#include "weapon_system.hpp"

#pragma mark _WeaponData

class _WeaponData : public WeaponData
{
    std::unordered_map<std::string, std::shared_ptr<WeaponSystem>> _weapon_systems;

public:
    void add_system(std::shared_ptr<WeaponSystem> system)
    {
        std::string key(system->name());
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        _weapon_systems[key] = system;
    }
    
    std::shared_ptr<WeaponSystem> weapon_system(const std::string &id) override
    {
        std::string key(id);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (_weapon_systems.find(key) != _weapon_systems.end())
            return _weapon_systems[key];
        
        return nullptr;
    }
};

#pragma mark WeaponData

std::shared_ptr<WeaponData> WeaponData::Make()
{
    std::shared_ptr<_WeaponData> data = std::make_shared<_WeaponData>();
    
    // *** NATO ***
    
    // AAM
    data->add_system(WeaponSystem::Make("Sidewinder", WeaponSystemType::AAM, AffiliationType::NATO, 10, 1, 1, false));
    // AAM_LONGRANGE
    data->add_system(WeaponSystem::Make("AMRAAM", WeaponSystemType::AAM_LONGRANGE, AffiliationType::NATO, 150, 2, 2, false));
    data->add_system(WeaponSystem::Make("Phoenix", WeaponSystemType::AAM_LONGRANGE, AffiliationType::NATO, 300, 2, 3, false));
    // SAM
    data->add_system(WeaponSystem::Make("Standard", WeaponSystemType::SAM, AffiliationType::NATO, 50, 2, 4, false));
    data->add_system(WeaponSystem::Make("Seadart", WeaponSystemType::SAM, AffiliationType::NATO, 50, 2, 2, false));
    data->add_system(WeaponSystem::Make("Seaslug", WeaponSystemType::SAM, AffiliationType::SOVIET, 30, 2, 1, false));
    // SSM
    data->add_system(WeaponSystem::Make("Harpoon", WeaponSystemType::SSM, AffiliationType::NATO, 110, 4, 9, true));
    data->add_system(WeaponSystem::Make("Exocet", WeaponSystemType::SSM, AffiliationType::NATO, 70, 7, 9, true));
    data->add_system(WeaponSystem::Make("Tomahawk", WeaponSystemType::SSM, AffiliationType::NATO, 500, 7, 9, true));
    // ASM
    data->add_system(WeaponSystem::Make("Walleye", WeaponSystemType::ASM, AffiliationType::NATO, 50, 12, 7, false));
    // AST
    data->add_system(WeaponSystem::Make("MK46", WeaponSystemType::AST, AffiliationType::NATO, 10, 3, 4, false));
    data->add_system(WeaponSystem::Make("MK48", WeaponSystemType::AST, AffiliationType::NATO, 50, 8, 5, false));
    data->add_system(WeaponSystem::Make("Tigerfish", WeaponSystemType::AST, AffiliationType::NATO, 40, 8, 4, false));
    // ASW
    data->add_system(WeaponSystem::Make("SUBROC", WeaponSystemType::ASROC, AffiliationType::NATO, 55, 4, 3, false));
    data->add_system(WeaponSystem::Make("Ikara", WeaponSystemType::ASROC, AffiliationType::NATO, 20, 3, 3, false));
    
    // *** SOVIET ***
    
    // AAM
    data->add_system(WeaponSystem::Make("Aphid", WeaponSystemType::AAM, AffiliationType::SOVIET, 10, 1, 1, false));
    // AAM_LONGRANGE
    data->add_system(WeaponSystem::Make("Apex", WeaponSystemType::AAM_LONGRANGE, AffiliationType::SOVIET, 150, 2, 1, false));
    // SAM
    data->add_system(WeaponSystem::Make("SA-N-1", WeaponSystemType::SAM, AffiliationType::SOVIET, 30, 2, 1, false));
    data->add_system(WeaponSystem::Make("SA-N-3", WeaponSystemType::SAM, AffiliationType::SOVIET, 40, 2, 2, false));
    data->add_system(WeaponSystem::Make("SA-N-6", WeaponSystemType::SAM, AffiliationType::SOVIET, 80, 2, 3, false));
    data->add_system(WeaponSystem::Make("SA-N-7", WeaponSystemType::SAM, AffiliationType::SOVIET, 25, 2, 4, true));
    // SSM
    data->add_system(WeaponSystem::Make("SS-N-2C", WeaponSystemType::SSM, AffiliationType::SOVIET, 50, 5, 5, false));
    data->add_system(WeaponSystem::Make("SS-N-3", WeaponSystemType::SSM, AffiliationType::SOVIET, 450, 15, 4, false));
    data->add_system(WeaponSystem::Make("SS-N-7", WeaponSystemType::SSM, AffiliationType::SOVIET, 60, 9, 7, false));
    data->add_system(WeaponSystem::Make("SS-N-12", WeaponSystemType::SSM, AffiliationType::SOVIET, 500, 9, 6, false));
    data->add_system(WeaponSystem::Make("SS-N-19", WeaponSystemType::SSM, AffiliationType::SOVIET, 500, 8, 7, false));
    data->add_system(WeaponSystem::Make("SS-N-22", WeaponSystemType::SSM, AffiliationType::SOVIET, 120, 6, 7, false));
    // ASM
    data->add_system(WeaponSystem::Make("AS-6", WeaponSystemType::ASM, AffiliationType::SOVIET, 300, 15, 5, true));
    data->add_system(WeaponSystem::Make("AS-7", WeaponSystemType::ASM, AffiliationType::SOVIET, 10, 7, 7, false));
    // AST
    data->add_system(WeaponSystem::Make("533MM", WeaponSystemType::AST, AffiliationType::SOVIET, 20, 3, 8, false));
    data->add_system(WeaponSystem::Make("400MM", WeaponSystemType::AST, AffiliationType::SOVIET, 7, 4, 3, false));
    // ASW
    data->add_system(WeaponSystem::Make("FRAS-1", WeaponSystemType::ASROC, AffiliationType::SOVIET, 25, 3, 4, false));

    return data;
}

std::shared_ptr<WeaponSystem> WeaponData::weapon_system(const std::string &id)
{
    return nullptr;
}
