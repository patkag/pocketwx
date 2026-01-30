#pragma once
#include <string>
#include "../logger.h"
#include "../display.h"
#include "../wx_sensor_module.h"
#include "../images/pocket_wx_welcome_img.h"

class MenuItem {
public:
    virtual ~MenuItem() = default;
    virtual void execute(Display& display, WxSensorModule& wx_sensor) = 0;
};

class MenuItemDisplayLogo : public MenuItem {
public:
    MenuItemDisplayLogo(){}
    void execute(Display& display, WxSensorModule& wx_sensor) override;
};

class MenuItemTemperature : public MenuItem {
public:
    MenuItemTemperature(){}
    void execute(Display& display, WxSensorModule& wx_sensor) override;
};



class MenuItemPressure : public MenuItem {
public:
    MenuItemPressure(){}
    void execute(Display& display, WxSensorModule& wx_sensor) override;
};

class MenuItemAltitude : public MenuItem {
public:
    MenuItemAltitude(){}
    void execute(Display& display, WxSensorModule& wx_sensor) override;
};

class MenuItemAllMeasurements : public MenuItem {
public:
    MenuItemAllMeasurements(){}
    void execute(Display& display, WxSensorModule& wx_sensor) override;
};
