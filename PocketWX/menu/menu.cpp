/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "menu.h"

void Menu::addMenuItem(std::unique_ptr<MenuItem> item)
{
    m_menu_items.push_back(move(item));
}

void Menu::run()
{

    // display welcome image
    m_display.imgToBuf(pocket_wx_welcome_img);
    m_display.renderDisplay();
    sleep_ms(1000);
    m_display.imgToBuf(pocket_wx_welcome_img_2);
    m_display.renderDisplay();

    RingBuffer battery_voltage;

    for (int i = 0; i < RING_BUFFER_SIZE; i++)
    {
        battery_voltage.pushBack(hardware_utils::getBatteryVoltage());
        sleep_ms(100);
    }

    while (true)
    {
        sleep_ms(200);
        m_display.cleanScreenBuf();
        execCurrent();

        // draw battery icon
        battery_voltage.pushBack(hardware_utils::getBatteryVoltage());
        m_display.drawBatteryIcon(((battery_voltage.getAvarage() - 3) * 10) / 3);
        Logger::sendLogMsg(Logger::LL_DEBUG, "Battery voltage: " + std::to_string(battery_voltage.getAvarage()));

        m_display.renderDisplay();
    }
}

void Menu::ButtonPressUp()
{
    Logger::sendLogMsg(Logger::LL_ERROR, "up button1");
    m_current_selection = (m_current_selection + 1) % m_menu_items.size();
    Logger::sendLogMsg(Logger::LL_INFO, "current menu selection: " + std::to_string(m_current_selection));
}

void Menu::ButtonPressDown()
{
    Logger::sendLogMsg(Logger::LL_ERROR, "down button1");
    m_current_selection = (m_current_selection + m_menu_items.size() -1) % m_menu_items.size();
    Logger::sendLogMsg(Logger::LL_INFO, "current menu selection: " + std::to_string(m_current_selection));
}

unsigned int Menu::getCurrentSelection()
{
    return m_current_selection;
}

void Menu::execCurrent()
{
    m_menu_items[m_current_selection]->execute(m_display, m_wx_sensor);
}
