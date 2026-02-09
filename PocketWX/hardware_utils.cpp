/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include "hardware_utils.h"

int hardware_utils::init_i2c()
{
    if(is_i2c_init_done==true)
    {
        //the init is already done, we don't need to do it again
        return 0;
    }
    else
    {
    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / bmp280_i2c example requires a board with I2C pins
        puts("Default I2C pins were not defined");
    return 1;
    #else

    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, SSD1306_I2C_CLK * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    #endif
    }
    return 0;
}

void hardware_utils::init_adc()
{
    adc_init();
    adc_gpio_init(GPIO_ADC_PIN);
    adc_select_input(ADC_INPUT_0);
}

RingBuffer::RingBuffer()
{
    m_sum=0;
    m_index=0;
    for(float i : m_buffer)
    {
        i=0;
    }
}

void RingBuffer::pushBack(float value)
{
    m_sum -= m_buffer[m_index];
    m_sum += value;
    m_buffer[m_index] = value;
    m_index=(m_index+1)%RING_BUFFER_SIZE;
}

float RingBuffer::getAvarage()
{
    return m_sum/RING_BUFFER_SIZE;
}