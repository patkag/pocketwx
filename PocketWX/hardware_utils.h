/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#pragma once

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "ssd1306_i2c.h"


namespace hardware_utils
{
    static bool is_i2c_init_done;
    int i2c_init();
}