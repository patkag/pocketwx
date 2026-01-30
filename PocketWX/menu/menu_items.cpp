#include "menu_items.h"

void MenuItemDisplayLogo::execute(Display &display, WxSensorModule& wx_sensor)
{
    display.imgToBuf(pocket_wx_welcome_img);
    sleep_ms(600);
    display.invertDisplayColor();
}

void MenuItemTemperature::execute(Display &display, WxSensorModule& wx_sensor)
{
    wx_sensor.updateData();
    display.putTextAt(10, 0, "Temperature");
    display.putTextAt(20, 20, "T " + std::to_string(wx_sensor.getTemp()));
    Logger::sendLogMsg(Logger::LL_INFO, "temperature: " + std::to_string(wx_sensor.getTemp()));
}

void MenuItemPressure::execute(Display &display, WxSensorModule& wx_sensor)
{
    wx_sensor.updateData();
    display.putTextAt(10, 0, "Pressure hpa");
    display.putTextAt(20, 20, "P " + std::to_string(wx_sensor.getPress()));
    Logger::sendLogMsg(Logger::LL_INFO, "pressure: " + std::to_string(wx_sensor.getPress()));
}

void MenuItemAltitude::execute(Display &display, WxSensorModule& wx_sensor)
{
    wx_sensor.updateData();
    display.putTextAt(10, 0, "Baro Alti");
    display.putTextAt(20, 16, "alt " + std::to_string(wx_sensor.getAlt()));
    display.putTextAt(20, 24, "  P " + std::to_string(wx_sensor.getPress()));
    Logger::sendLogMsg(Logger::LL_INFO, "altitude menu item: " + std::to_string(wx_sensor.getAlt()));
}

void MenuItemAllMeasurements::execute(Display &display, WxSensorModule& wx_sensor)
{
wx_sensor.updateData();
    display.putTextAt(10, 0, "all measurements");
    display.putTextAt(5,  8, "  T " + std::to_string(wx_sensor.getTemp()));
    display.putTextAt(5, 16, "  P " + std::to_string(wx_sensor.getPress()));
    display.putTextAt(5, 24, "alt " + std::to_string(wx_sensor.getAlt()));
    Logger::sendLogMsg(Logger::LL_INFO, "all measurements menu item");
}