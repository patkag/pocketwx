#pragma once

#include <string>
#include "ssd1306_i2c.h"
#include "logger.h"

void init_display();

class Display {
public:
    Display();

    void showMessage(const std::string& msg);
    int putTextAt(int16_t x, int16_t y, const std::string& msg);

    void imgToBuf(uint8_t*);
    void renderDisplay();
    void cleanScreenBuf();
    void invertDisplayColor();

    void static SSD1306_screen_flash();
    void static screenTest();

private:

    struct render_area m_frame_area = {
        start_col: 0,
        end_col : SSD1306_WIDTH - 1,
        start_page : 0,
        end_page : SSD1306_NUM_PAGES - 1
        };

    uint8_t m_screen_buf[SSD1306_BUF_LEN];

    bool m_is_display_inverted;


};