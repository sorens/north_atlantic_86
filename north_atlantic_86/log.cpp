//
//  log.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/18/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "log.hpp"
#include <iomanip>
#include <syslog.h>

#pragma mark LogLine

LogLine::LogLine(LogLevel level) : _level(level)
{
}

const std::string LogLine::convert(const LogLine &log)
{
    std::ostringstream ss;
    // TODO move to its own log file so we can make this field a key
//    ss << std::left << std::setw(5) << "NA86";
//    ss << " ";
    ss << std::left << std::setw(10) << level_to_string(log.level());
    ss << " ";
    ss << log.message();
    ss << std::endl;
    
    return ss.str();
}

const std::string LogLine::level_to_string(LogLevel level)
{
    switch (level) {
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::VERBOSE:
            return "VERBOSE";
    }
}

const LogLevel LogLine::level() const
{
    return _level;
}

const std::string LogLine::message() const
{
    return _stream.str();
}

#pragma mark Log

void Log::write_log(LogLevel level, const std::string &message)
{
    syslog(static_cast<int>(level), "%s", message.c_str());
}
