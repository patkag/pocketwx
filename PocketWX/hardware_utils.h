/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "ssd1306_i2c.h"

#define GPIO_ADC_PIN 26
#define ADC_INPUT_0 0
#define RING_BUFFER_SIZE 10

#define GPIO_BUTTON_UP 9
#define GPIO_BUTTON_DOWN 8
#define GPIO_BUTTON_XX 7
#define GPIO_BUTTON_X 6

namespace hardware_utils
{
    static bool is_i2c_init_done;
    int init_i2c();
    void init_adc();
    inline float getBatteryVoltage()
    {
        // scale and add the voltage divider error and Schottky diode voltage drop
        return (adc_read() * 3.3f / (1 << 12) * 2) + .55;
    }
}

class RingBuffer
{
public:
    RingBuffer();
    float getAvarage();
    void pushBack(float value);
private:
    float m_buffer[RING_BUFFER_SIZE];
    unsigned int m_index;
    float m_sum;
};