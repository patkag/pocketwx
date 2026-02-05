/*------------------------------------------------------/
/ Copyright (c) 2026, patkag
/ Released under the GNU General Public License version 3
/ refer to https://opensource.org/license/gpl-3-0
/------------------------------------------------------*/

#include <stdio.h>
#include <cmath>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "bmep280.h"

#include "ssd1306_i2c.h"
#include "display.h"
#include "menu/menu.h"


#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

#ifndef PICO_DEFAULT_LED_PIN
#warning blink_simple example requires a board with a regular LED
#endif

// Initialize the GPIO for the LED
void pico_led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
}

// Turn the LED on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}


static Menu* menu;
uint gpio;
uint32_t events;

void buttonCallback_two(uint gpios, uint32_t eventss)
{
    gpio = gpios;
    sleep_ms(20);
    if (0 == gpio_get(gpio))
    {
        switch (gpios)
        {
        case GPIO_BUTTON_DOWN:
            menu->ButtonPressDown();
            break;
        case GPIO_BUTTON_UP:
            menu->ButtonPressUp();
            break;
        }
    }
}
// ========================= MAIN =========================
int main_menu() {
    Display display;
    menu=new Menu(display);
    display.showMessage("Main Menu");

    menu->addMenuItem(make_unique<MenuItemDisplayLogo>());
    menu->addMenuItem(make_unique<MenuItemTemperature>());
    menu->addMenuItem(make_unique<MenuItemPressure>());
    menu->addMenuItem(make_unique<MenuItemAltitude>());
    menu->addMenuItem(make_unique<MenuItemAllMeasurements>());

    
    gpio_init(GPIO_BUTTON_DOWN);
    gpio_init(GPIO_BUTTON_UP);
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_DOWN, GPIO_IRQ_EDGE_FALL, true, &buttonCallback_two);
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_UP,   GPIO_IRQ_EDGE_FALL, true, &buttonCallback_two);

    menu->run();
    return 0;
}




void init_all()
{
    stdio_init_all();
    pico_led_init();
    //display init
    hardware_utils::i2c_init();
    init_display();
}



int main()
{
    init_all();
    printf("Hello, init!\n");

    main_menu();
    int i=0;
    while(true)
    {

        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}
