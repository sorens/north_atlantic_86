//
//  file.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/19/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "debug.hpp"
#include "file.hpp"

#pragma mark _File

#define INVALID             -1

class _file : public file
{
    std::fstream _fstream;
    file_mode _mode;
    std::string _path;

public:
    _file(const std::string &path) : _path(path)
    {
    }
    
    void close() override
    {
        _fstream.close();
    }
    
    bool open(file_mode mode) override
    {
        if (_fstream.is_open())
            return false;
        
        _mode = mode;
        
        std::ios_base::openmode openMode = (std::ios_base::openmode)0;
        if (mode & file_mode_open_append)
            openMode |= std::ios_base::app;
        if (mode & file_mode_open_binary)
            openMode |= std::ios_base::binary;
        if (mode & file_mode_open_read)
            openMode |= std::ios_base::in;
        if (mode & file_mode_open_truncate)
            openMode |= std::ios_base::trunc;
        
        _fstream.open(_path, openMode);
        return _fstream.good();
    }
    
    ssize_t read(char *buf, size_t size) override
    {
        runtime_assert(buf);
        runtime_assert(size);
        
        if (!_fstream.good())
            return INVALID;
        
        auto initial = _fstream.tellg();
        _fstream.read(buf, size);
        
        if (!_fstream.good() && !_fstream.eof())
            return INVALID;
        
        return _fstream.tellg() - initial;
    }
    
    off_t size() override
    {
        struct stat ss;
        off_t size = 0;
        if (stat(_path.c_str(), &ss) >= 0)
            size = ss.st_size;
        
        return size;
    }
    
    ssize_t write(const char *buf, size_t size) override
    {
        // TODO implement once we need to write files
        return INVALID;
    }
};

#pragma mark File

void file::close()
{
    runtime_assert_not_reached();
}

std::shared_ptr<file> file::Make(const std::string &path)
{
    return std::make_shared<_file>(path);
}

bool file::open(file_mode mode)
{
    runtime_assert_not_reached();
}

ssize_t file::read(char *buf, size_t size)
{
    runtime_assert_not_reached();
}

off_t file::size()
{
    runtime_assert_not_reached();
}

ssize_t file::write(const char *buf, size_t size)
{
    runtime_assert_not_reached();
}
