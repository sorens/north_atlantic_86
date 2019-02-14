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

class na_exception : public std::exception
{
public:
    na_exception() {}
    na_exception(const std::string &info) : _info(info) {}
    
    virtual const char * info() const noexcept
    {
        return _info.c_str();
    }
    
    virtual const char * what() const noexcept
    {
        std::stringstream ss;
        ss << std::exception::what();
        if (!_info.empty())
            ss << " {" << _info << "}";
            
        return ss.str().c_str();
    }

private:
    std::string _info;
};
