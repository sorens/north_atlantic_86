//
//  debug.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <cstdlib>
#include "log.hpp"

#define runtime_assert(condition)                                           \
    do {                                                                    \
        if (!(condition)) {                                                 \
            logerror("ASSERTION FAILED: <" << __PRETTY_FUNCTION__ <<        \
            ", line " << __LINE__ << ">: " << #condition);                  \
            abort();                                                        \
        }                                                                   \
    } while(0)

#define runtime_assert_not_reached()                                        \
    do {                                                                    \
        logerror("ASSERTION FAILED: <" << __PRETTY_FUNCTION__ <<            \
        ", line " << __LINE__ <<                                            \
        ">: Should not be reached.");                                       \
        abort();                                                            \
    } while (0)

#ifndef NDEBUG
    #define debug_assert(condition)         runtime_assert(condition)
    #define debug_assert_not_reached()      runtime_assert_not_reached()
    #define debug_assert_unused(condition)  debug_assert(condition)
#else // NDEBUG
    #define debug_assert(condition)                                         \
        do {                                                                \
        } while (0)
    #define debug_assert_not_reached()                                      \
        do {                                                                \
        } while (0)
    #define debug_assert_unused(condition)  ((void)condition)
#endif // NDEBUG
