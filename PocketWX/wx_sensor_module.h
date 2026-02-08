/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#pragma once

#include "bmep280.h"
#include "hardware_utils.h"
#include "logger.h"
#include <string>

class WxSensorModule
{
public:
    WxSensorModule();
    
    float getTemp();
    float getPress();
    float getHumidity();
    float getAlt();
    int updateData();

private:       

    int initWxSensorModule();
    bmp280_calib_param m_calib_params;

    float m_temp;
    float m_pressure;
    float m_humidity;
    float m_alt;
    float m_initial_pressure;
    int   m_initial_altitude;

    //constants for barometric altitude calculation
    const float kLapseRate = 0.0065f; // K/m
    const float kTemp0 = 288.15f;      // 15 C in K
    const float kExponent = 0.190284f;

};