//
//  file.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <fstream>
#include <sys/stat.h>

typedef unsigned FileMode;
enum : unsigned
{
    FileModeOpenRead        = (1 << 0),
    FileModeOpenWrite       = (1 << 1),
    FileModeOpenBinary      = (1 << 2),
    FileModeOpenAppend      = (1 << 3),
    FileModeOpenTruncate    = (1 << 4),
};

class File
{
public:
    virtual void close();
    static std::shared_ptr<File> Make(const std::string &path);
    virtual bool open(FileMode mode);
    virtual ssize_t read(char *buf, size_t size);
    virtual off_t size();
    virtual ssize_t write(const char *buf, size_t size);
};
