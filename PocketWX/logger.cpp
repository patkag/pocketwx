/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "logger.h"
#include <format>

Logger* Logger::m_instance_ptr = nullptr;
const std::string Logger::m_labels[3] = {"ERROR", "WARNING", "INFO"};

Logger::Logger()
{
    m_log_level=Logger::LL_INFO;
}

void Logger::setLogLevel(Logger::LogLevel level)
{
    m_log_level = level;
}

Logger::LogLevel Logger::getLogLevel()
{
    return m_log_level;
}



void Logger::sendLogMsg(LogLevel logLvl, const std::string msg)
{
    Logger* inst = getInstance();
    if (logLvl <= inst->getLogLevel())
    {
        printf("%-8s: %s\n", m_labels[logLvl].c_str(), msg.c_str());
    }
}

Logger* Logger::getInstance()
{
    if (m_instance_ptr == nullptr)
    {
        m_instance_ptr = new Logger();
    }
    return m_instance_ptr;
}