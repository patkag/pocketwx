#include "display.h"


void init_display()
{
    //TODO make sure i2c init was done
        //display init
    SSD1306_init();
    
    // Initialize render area for entire frame (SSD1306_WIDTH pixels by SSD1306_NUM_PAGES pages)
    //struct render_area frame_area = {
    //    start_col: 0,
    //    end_col : SSD1306_WIDTH - 1,
    //    start_page : 0,
    //    end_page : SSD1306_NUM_PAGES - 1
    //    };

    //calc_render_area_buflen(&frame_area);

    // zero the entire display
    //probably it's not needed
    //uint8_t buf[SSD1306_BUF_LEN];
    //memset(buf, 0, SSD1306_BUF_LEN);
    //render(buf, &frame_area);
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

void Display::screenTest()
{
    uint8_t buf[SSD1306_BUF_LEN];
    memset(buf, 0, SSD1306_BUF_LEN);
    struct render_area frame_area = {
        start_col : 0,
        end_col : SSD1306_WIDTH - 1,
        start_page : 0,
        end_page : SSD1306_NUM_PAGES - 1
    };

    calc_render_area_buflen(&frame_area);
    char *text[] = {
        "A long time ago",
        "  on an OLED ",
        "   display",
        " far far away",
        "Lived a small",
        "red raspberry",
        "by the name of",
        "    PICO"};

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        WriteString(buf, 5, y, text[i]);
        y += 8;
    }
    render(buf, &frame_area);
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