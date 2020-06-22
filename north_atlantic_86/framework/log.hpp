//
//  log.hpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/18/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#pragma once

#include <sstream>
#include <string>

#define logerror(...)       Log::write_log(LogLevel::ERROR, LogLine::convert(LogLine(LogLevel::ERROR) << __VA_ARGS__))
#define logwarn(...)        Log::write_log(LogLevel::WARNING, LogLine::convert(LogLine(LogLevel::WARNING) << __VA_ARGS__))
#define loginfo(...)        Log::write_log(LogLevel::INFO, LogLine::convert(LogLine(LogLevel::INFO) << __VA_ARGS__))
#define logverbose(...)     Log::write_log(LogLevel::VERBOSE, LogLine::convert(LogLine(LogLevel::VERBOSE) << __VA_ARGS__))

enum class LogLevel
{
    ERROR = 0,
    WARNING,
    INFO,
    VERBOSE
};

class LogLine
{
public:
    LogLine(LogLevel level);
    
    template <typename T>
    LogLine &operator<<(T const &value)
    {
        _stream << value;
        return *this;
    }
    
    static const std::string convert(const LogLine &log);
    static const std::string level_to_string(LogLevel level);
    const LogLevel level() const;
    const std::string message() const;

private:
    LogLevel _level;
    std::ostringstream _stream;
};

class Log
{
public:
    static void initialize(const std::string& file_path, LogLevel level, bool stdout_to_log = false, bool stderr_to_log = false);
    static void change_log_level(LogLevel level);
    static void write_log(LogLevel level, const std::string &message);
private:
    static LogLevel LOG_LEVEL;
    static std::string LOG_PATH;
};
