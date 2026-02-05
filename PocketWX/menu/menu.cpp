/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "menu.h"

void Menu::addMenuItem(unique_ptr<MenuItem> item)
{
    m_menu_items.push_back(move(item));
}

void Menu::run()
{

    m_display.imgToBuf(pocket_wx_welcome_img);

    m_display.renderDisplay();

    sleep_ms(2000);

    while (true)
    {
        sleep_ms(200);
        m_display.cleanScreenBuf();
        execCurrent();
        m_display.renderDisplay();
    }
}

void Menu::ButtonPressUp()
{
    Logger::sendLogMsg(Logger::LL_ERROR, "up button1");
    if (m_current_selection + 1 == m_menu_items.size())
    {
        m_current_selection = 0;
    }
    else
    {
        m_current_selection++;
    }
    Logger::sendLogMsg(Logger::LL_INFO, "current menu selection: " + to_string(m_current_selection));
}

void Menu::ButtonPressDown()
{
    Logger::sendLogMsg(Logger::LL_ERROR, "down button1");
    if (m_current_selection == 0)
    {
        m_current_selection = m_menu_items.size() - 1;
    }
    else
    {
        m_current_selection--;
    }
    Logger::sendLogMsg(Logger::LL_INFO, "current menu selection: " + to_string(m_current_selection));
}
unsigned int Menu::getCurrentSelection()
{
    return m_current_selection;
}
void Menu::execCurrent()
{
    m_menu_items[m_current_selection]->execute(m_display, m_wx_sensor);
}


