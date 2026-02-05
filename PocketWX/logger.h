/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

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
        LL_INFO    = 2
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
    static const std::string m_labels[3];

};