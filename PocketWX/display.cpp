/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "display.h"

void init_display()
{
    //TODO make sure i2c init was done
        //display init
    SSD1306_init();
    
}

Display::Display()
{
    calc_render_area_buflen(&m_frame_area);
    cleanScreenBuf();
    renderDisplay();
    m_is_display_inverted=false;
}


void Display::showMessage(const std::string& msg)
{
    uint8_t myscreen_buf[SSD1306_BUF_LEN];
    memset(myscreen_buf, 0, SSD1306_BUF_LEN);

    //sprintf(str_buffer, "T:%.2f  C", temperature / 100.f);
    Logger::sendLogMsg(Logger::LL_INFO,"Message to display: "+msg);
    WriteString(myscreen_buf, 5, 8, msg.c_str());
    render(myscreen_buf, &m_frame_area);
}

int Display::putTextAt(int16_t x, int16_t y, const std::string& msg)
{
    //TODO check if we need to clear the screen buffer under the new text
    //TODO check for valid coordonates, text size
    WriteString(m_screen_buf, x, y, msg.c_str());
    return 0;
}

void Display::SSD1306_screen_flash()
{

    SSD1306_send_cmd(SSD1306_SET_ALL_ON);    // Set all pixels on
    sleep_ms(2000);
    SSD1306_send_cmd(SSD1306_SET_ENTIRE_ON); // go back to following RAM for pixel state
    sleep_ms(100);

}

void Display::renderDisplay()
{
    render(m_screen_buf, &m_frame_area);
}

void Display::cleanScreenBuf()
{
    memset(m_screen_buf, 0, SSD1306_BUF_LEN);
}

void Display::imgToBuf(uint8_t* buf)
{
    memcpy( m_screen_buf, buf, SSD1306_BUF_LEN );
}

void Display::invertDisplayColor()
{
    if(m_is_display_inverted)
    {
        SSD1306_send_cmd(SSD1306_SET_NORM_DISP);
    }
    else
    {
        SSD1306_send_cmd(SSD1306_SET_INV_DISP);
    }
    m_is_display_inverted=!m_is_display_inverted;
}

void Display::drawBatteryIcon(unsigned int level)
{
    //TODO optimize it
    switch (level)
    {
    case 0:
        DrawImageAt(m_screen_buf, SSD1306_WIDTH - BATTERY_ICON_IMG_WIDTH, 0, battery_icon_0, BATTERY_ICON_IMG_WIDTH, BATTERY_ICON_IMG_HEIGHT);
        break;
    case 1:
        DrawImageAt(m_screen_buf, SSD1306_WIDTH - BATTERY_ICON_IMG_WIDTH, 0, battery_icon_1, BATTERY_ICON_IMG_WIDTH, BATTERY_ICON_IMG_HEIGHT);
        break;
    case 2:
        DrawImageAt(m_screen_buf, SSD1306_WIDTH - BATTERY_ICON_IMG_WIDTH, 0, battery_icon_2, BATTERY_ICON_IMG_WIDTH, BATTERY_ICON_IMG_HEIGHT);
        break;
    case 3:
        DrawImageAt(m_screen_buf, SSD1306_WIDTH - BATTERY_ICON_IMG_WIDTH, 0, battery_icon_3, BATTERY_ICON_IMG_WIDTH, BATTERY_ICON_IMG_HEIGHT);
        break;
    default:
        DrawImageAt(m_screen_buf, SSD1306_WIDTH - BATTERY_ICON_IMG_WIDTH, 0, battery_icon_0, BATTERY_ICON_IMG_WIDTH, BATTERY_ICON_IMG_HEIGHT);
        break;
    }
}