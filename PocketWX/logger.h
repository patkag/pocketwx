#pragma once

#include <string>
#include "hardware_utils.h"


class Logger
{
    public:
    enum LogLevel
    {
        LL_ERROR   = 0,
        LL_WARNING = 1,
        LL_INFO    = 2,
        LL_DEBUG   = 3
    };
    static void sendLogMsg(LogLevel logLvl, const std::string msg);

    LogLevel getLogLevel();
    void setLogLevel(LogLevel level);
    static Logger* getInstance();
    Logger(const Logger &obj) = delete;

    private:

    Logger();
    
    static Logger *m_instance_ptr;
    LogLevel m_log_level;
    static const std::string m_labels[4];

};