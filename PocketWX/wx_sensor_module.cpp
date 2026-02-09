/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "wx_sensor_module.h"
#include <math.h>

int WxSensorModule::initWxSensorModule()
{
    int ret = hardware_utils::init_i2c();
    
    if(ret == 0)
    {
        // configure BMP280
        bmp280_init();

        // retrieve fixed compensation params
        bmp280_get_calib_params(&m_calib_params); 
    }
    return ret;       
}

WxSensorModule::WxSensorModule()
{
    initWxSensorModule();
    m_temp = -1;
    m_pressure = -1;
    m_humidity = -1;
    m_alt = -1;
    //let's give the sensor a bit of time to get up to speed
    sleep_ms(100);
    updateData();
    m_initial_pressure = m_pressure;
    m_initial_altitude = 515;
    Logger::sendLogMsg(Logger::LL_INFO, "initial pressure value: " + std::to_string(m_initial_pressure));
}

float WxSensorModule::getTemp()
{
    return m_temp;
}

float WxSensorModule::getPress()
{
    return m_pressure;
}

float WxSensorModule::getHumidity()
{
    return m_humidity;
}

float WxSensorModule::getAlt()
{
    float ratio = m_pressure / m_initial_pressure;
    float deltaH = (kTemp0 / kLapseRate) * (1.0f - pow(ratio, kExponent));
    
    return m_initial_altitude + deltaH;
}

int WxSensorModule::updateData()
{
    int32_t raw_temperature;
    int32_t raw_pressure;

    bmp280_read_raw(&raw_temperature, &raw_pressure);
    int32_t temperature = bmp280_convert_temp(raw_temperature, &m_calib_params);
    int32_t pressure = bmp280_convert_pressure(raw_pressure, raw_temperature, &m_calib_params);
    
    m_temp = temperature / 100.f;
    m_pressure = pressure / 100.f; //to get the pressure in hPa
    
    return 0;
}