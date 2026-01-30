#include "wx_sensor_module.h"

int WxSensorModule::initWxSensorModule()
{
    int ret = hardware_utils::i2c_init();
    
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
    return m_alt;
}

int WxSensorModule::updateData()
{
    int32_t raw_temperature;
    int32_t raw_pressure;

    bmp280_read_raw(&raw_temperature, &raw_pressure);
    int32_t temperature = bmp280_convert_temp(raw_temperature, &m_calib_params);
    int32_t pressure = bmp280_convert_pressure(raw_pressure, raw_temperature, &m_calib_params);
    
    m_temp = temperature / 100.f;
    m_pressure = pressure / 1000.f;
    
    return 0;
}