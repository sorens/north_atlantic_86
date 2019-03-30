//
//  exception.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/13/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

class na_exception : public std::runtime_error
{
public:
    na_exception() : std::runtime_error("unknown error") {}
    na_exception(const std::string &info) : std::runtime_error(info) {}
};
