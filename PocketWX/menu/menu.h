/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../wx_sensor_module.h"
#include "../images/pocket_wx_welcome_img.h"
#include "../display.h"
#include "../logger.h"
#include "../hardware_utils.h"
#include "menu_items.h"

class Menu
{

public:
    Menu(Display &d) : m_display(d) {}

    void addMenuItem(std::unique_ptr<MenuItem> item);

    void run();
    unsigned int getCurrentSelection();
    void execCurrent();

    void ButtonPressUp();
    void ButtonPressDown();

private:
    std::vector<std::unique_ptr<MenuItem>> m_menu_items;
    unsigned int m_current_selection;
    Display &m_display;
    WxSensorModule m_wx_sensor;
};
