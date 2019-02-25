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

typedef unsigned file_mode;
enum : unsigned
{
    file_mode_open_read     = (1 << 0),
    file_mode_open_write    = (1 << 1),
    file_mode_open_binary   = (1 << 2),
    file_mode_open_append   = (1 << 3),
    file_mode_open_truncate = (1 << 4),
};

class file
{
public:
    virtual void close();
    static std::shared_ptr<file> Make(const std::string &path);
    virtual bool open(file_mode mode);
    virtual ssize_t read(char *buf, size_t size);
    virtual off_t size();
    virtual ssize_t write(const char *buf, size_t size);
};
