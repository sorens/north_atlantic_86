//
//  log.cpp
//  north_atlantic_86
//
//  Created by STEPHEN ORENS on 2/18/19.
//  Copyright © 2019 STEPHEN ORENS. All rights reserved.
//

#include "log.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

#pragma mark LogLine

LogLine::LogLine(LogLevel level) : _level(level)
{
}

const std::string LogLine::convert(const LogLine &log)
{
    std::ostringstream ss;
    auto tty = isatty(STDOUT_FILENO);
    
    if (tty) {
        auto t = time(NULL);
        struct tm tmp;
        if (!localtime_r(&t, &tmp)) {
            // assert?
            return "";
        }
        
        char str[32];
        if (!strftime(str, sizeof(str), "%F %T", &tmp)) {
            // asert!
            return "";
        }
        
        ss << std::setw(19) << std::left << str;
        ss << " ";
    }
    
    ss << std::left << std::setw(4) << level_to_string(log.level());
    ss << " ";
    
//        if(tty) {
//            ss << std::left << std::setw(6) << "[PID]";
//            ss << " ";
//            ss << std::left << std::setw(10) << "process_name";
//            ss << " ";
//        }
    
    ss << std::left << std::setw(4) << "NA86";
    ss << " ";
    ss << log.message();
    ss << std::endl;
    
    return ss.str();
}

const std::string LogLine::level_to_string(LogLevel level)
{
    switch (level) {
        case LogLevel::ERROR:
            return "ERRO";
        case LogLevel::WARNING:
            return "WARN";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::VERBOSE:
            return "VERB";
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

LogLevel Log::LOG_LEVEL = LogLevel::VERBOSE;
std::string Log::LOG_PATH  = "";

void Log::initialize(const std::string& file_path, LogLevel level, bool stdout_to_log, bool stderr_to_log)
{
    LOG_LEVEL = level;
    
    std::string home(getenv("HOME"));
    if (file_path != "") {
        auto pos = file_path.find("~");
        if (pos != std::string::npos) {
            if (home != "") {
                Log::LOG_PATH = home + file_path.substr(pos+1, file_path.length());
            }
        }
        else {
            Log::LOG_PATH = file_path;
        }
    }
    
    if (Log::LOG_PATH == "") {
          Log::LOG_PATH = "./na86.log";
    }
    
    if (stdout_to_log && LOG_PATH != "") {
        // redirect stdout to our log file
        freopen(LOG_PATH.c_str(), "a", stdout);
    }
    
    if (stderr_to_log && LOG_PATH != "") {
        // redirect stderr to our log file
        freopen(LOG_PATH.c_str(), "a", stderr);
    }
}

void Log::change_log_level(LogLevel level)
{
    Log::LOG_LEVEL = level;
}

void Log::write_log(LogLevel level, const std::string &message)
{
    if (level <= Log::LOG_LEVEL && Log::LOG_PATH != "") {
        std::ofstream os;
        os.open(Log::LOG_PATH, std::ios_base::app);
        if (os.is_open()) {
            os << message;
            os.flush();
            os.close();
        }
    }
}
